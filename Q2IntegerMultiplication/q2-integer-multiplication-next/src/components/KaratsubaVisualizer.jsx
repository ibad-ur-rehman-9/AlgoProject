"use client"
import React, { useState, useEffect } from "react";
import { Play, SkipForward, RotateCcw, Pause } from "lucide-react";

const KaratsubaVisualizer = () => {
  const [fileData, setFileData] = useState([]); // loaded number pairs from JSON
  const [selectedFile, setSelectedFile] = useState(""); // selected filename
  const [selectedPairIndex, setSelectedPairIndex] = useState(0); // pick pair in file
  const [num1, setNum1] = useState("1234");
  const [num2, setNum2] = useState("5678");
  const [steps, setSteps] = useState([]);
  const [currentStep, setCurrentStep] = useState(0);
  const [isPlaying, setIsPlaying] = useState(false);
  const [tree, setTree] = useState(null);

  const handleFileUpload = async (e) => {
    const file = e.target.files?.[0];
    if (!file) {
      setFileData([]);
      setSelectedFile("");
      return;
    }

    setSelectedFile(file.name);
    setSelectedPairIndex(0);

    try {
      const text = await file.text();
      const data = JSON.parse(text);

      // Validate that it's an array of objects with 'a' and 'b' properties
      if (
        Array.isArray(data) &&
        data.length > 0 &&
        "a" in data[0] &&
        "b" in data[0]
      ) {
        setFileData(data);
        setNum1(data[0].a.toString());
        setNum2(data[0].b.toString());
      } else {
        throw new Error("Invalid JSON format. Expected array of {a, b} pairs.");
      }
    } catch (err) {
      console.error("Failed to load file:", err);
      alert(`Error loading file: ${err.message}`);
      setFileData([]);
      setSelectedFile("");
    }
  };

  // Karatsuba algorithm with step tracking
  const karatsuba = (x, y, depth = 0, parentId = null, position = "root") => {
    const stepData = [];
    let nodeId = 0;

    const multiply = (a, b, d, pid, pos) => {
      const id = nodeId++;
      const node = {
        id,
        x: a,
        y: b,
        depth: d,
        parentId: pid,
        position: pos,
        children: [],
        result: null,
        operations: [],
      };

      // Base case
      if (a < 10 || b < 10) {
        const result = a * b;
        node.result = result;
        node.operations.push(`Base case: ${a} × ${b} = ${result}`);
        stepData.push({ ...node, type: "base" });
        return { result, node };
      }

      // Calculate size and split point
      const n = Math.max(a.toString().length, b.toString().length);
      const m = Math.floor(n / 2);
      const power = Math.pow(10, m);

      // Split numbers
      const high1 = Math.floor(a / power);
      const low1 = a % power;
      const high2 = Math.floor(b / power);
      const low2 = b % power;

      node.operations.push(`Split ${a} = ${high1} × 10^${m} + ${low1}`);
      node.operations.push(`Split ${b} = ${high2} × 10^${m} + ${low2}`);
      stepData.push({ ...node, type: "split", high1, low1, high2, low2, m });

      // Three recursive multiplications
      node.operations.push(`Computing z2 = ${high1} × ${high2}`);
      const z2Result = multiply(high1, high2, d + 1, id, "z2");
      node.children.push(z2Result.node);

      node.operations.push(`Computing z0 = ${low1} × ${low2}`);
      const z0Result = multiply(low1, low2, d + 1, id, "z0");
      node.children.push(z0Result.node);

      const sum1 = high1 + low1;
      const sum2 = high2 + low2;
      node.operations.push(
        `Computing z1 = (${high1}+${low1}) × (${high2}+${low2}) = ${sum1} × ${sum2}`
      );
      const z1TempResult = multiply(sum1, sum2, d + 1, id, "z1");
      node.children.push(z1TempResult.node);

      const z2 = z2Result.result;
      const z0 = z0Result.result;
      const z1 = z1TempResult.result - z2 - z0;

      node.operations.push(`z2 = ${z2}, z0 = ${z0}`);
      node.operations.push(
        `z1 = ${z1TempResult.result} - ${z2} - ${z0} = ${z1}`
      );

      // Combine results
      const result = z2 * power * power + z1 * power + z0;
      node.operations.push(
        `Result = ${z2}×10^${m * 2} + ${z1}×10^${m} + ${z0} = ${result}`
      );
      node.result = result;

      stepData.push({ ...node, type: "combine", z0, z1, z2, m });

      return { result, node };
    };

    const { result, node } = multiply(
      parseInt(x),
      parseInt(y),
      depth,
      parentId,
      position
    );
    return { result, steps: stepData, tree: node };
  };

  const executeAlgorithm = () => {
    if (!num1 || !num2) return;

    const x = parseInt(num1);
    const y = parseInt(num2);

    if (isNaN(x) || isNaN(y)) return;

    const { result, steps: newSteps, tree: newTree } = karatsuba(x, y);
    setSteps(newSteps);
    setTree(newTree);
    setCurrentStep(0);
    setIsPlaying(false);
  };

  useEffect(() => {
    executeAlgorithm();
  }, []);

  useEffect(() => {
    let interval;
    if (isPlaying && currentStep < steps.length - 1) {
      interval = setInterval(() => {
        setCurrentStep((prev) => {
          if (prev >= steps.length - 1) {
            setIsPlaying(false);
            return prev;
          }
          return prev + 1;
        });
      }, 1000);
    } else if (currentStep >= steps.length - 1) {
      setIsPlaying(false);
    }
    return () => clearInterval(interval);
  }, [isPlaying, currentStep, steps.length]);
const [selectedNodeId, setSelectedNodeId] = useState(null);

  const renderTree = (node, x = 400, y = 50, level = 0, offset = 200) => {
    if (!node) return null;

    const currentStepNode = steps[currentStep];
    const isActive = currentStepNode && currentStepNode.id === node.id;
    const isPast = currentStepNode && currentStepNode.id > node.id;
    const isSelected = selectedNodeId === node.id; // new

    const elements = [];

    // Draw lines to children
    if (node.children && node.children.length > 0) {
      const childOffset = offset / 2;
      const positions = [x - offset, x, x + offset];

      node.children.forEach((child, idx) => {
        const childX = positions[idx] || x;
        const childY = y + 120;

        elements.push(
          <line
            key={`line-${node.id}-${child.id}`}
            x1={x}
            y1={y + 30}
            x2={childX}
            y2={childY - 10}
            stroke={isActive ? "#3b82f6" : isPast ? "#10b981" : "#cbd5e1"}
            strokeWidth="2"
          />
        );

        elements.push(
          ...renderTree(child, childX, childY, level + 1, childOffset)
        );
      });
    }

    // Draw node
    elements.push(
      <g
        key={`node-${node.id}`}
        onClick={() => setSelectedNodeId(node.id)}
        style={{ cursor: "pointer" }}
      >
        <rect
          x={x - 60}
          y={y - 10}
          width="120"
          height="40"
          rx="5"
          fill={isActive ? "#3b82f6" : isPast ? "#10b981" : "#f1f5f9"}
          stroke={isActive ? "#2563eb" : isPast ? "#059669" : "#94a3b8"}
          strokeWidth="2"
        />
        <text
          x={x}
          y={y + 10}
          textAnchor="middle"
          fontSize="12"
          fontWeight="600"
          fill={isActive || isPast ? "white" : "#1e293b"}
        >
          {node.x} × {node.y}
        </text>
        {node.result !== null && (
          <text
            x={x}
            y={y + 24}
            textAnchor="middle"
            fontSize="10"
            fill={isActive || isPast ? "white" : "#64748b"}
          >
            = {node.result}
          </text>
        )}
        {node.position !== "root" && (
          <text
            x={x}
            y={y - 15}
            textAnchor="middle"
            fontSize="9"
            fill="#64748b"
            fontWeight="500"
          >
            {node.position}
          </text>
        )}
      </g>
    );

    return elements;
  };

  const calculateTreeHeight = (node) => {
    if (!node || !node.children || node.children.length === 0) return 1;
    return 1 + Math.max(...node.children.map(calculateTreeHeight));
  };
 
  const treeHeight = tree ? calculateTreeHeight(tree) : 1;
  const svgHeight = Math.max(400, treeHeight * 120 + 100);

  return (
    <div className="w-full h-screen bg-gradient-to-br from-slate-50 to-slate-100 p-6 overflow-auto">
      <div className="max-w-7xl mx-auto">
        <div className="mb-6">
          <h1 className="text-3xl font-bold text-slate-800 mb-2">
            Karatsuba Multiplication Visualizer
          </h1>
          <p className="text-slate-600">
            Watch the divide-and-conquer algorithm in action
          </p>
        </div>
        <div className="bg-white rounded-lg shadow-lg p-6 mb-6">
          <div className="flex text-black flex-col gap-4 items-start flex-wrap">
            <div className="flex-1 min-w-[200px]">
              <label className="block text-sm font-medium text-slate-700 mb-2">
                Upload JSON File
              </label>
              <input
                type="file"
                accept=".json"
                onChange={handleFileUpload}
                className="w-full px-4 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 file:mr-4 file:py-2 file:px-4 file:rounded-lg file:border-0 file:text-sm file:font-semibold file:bg-blue-50 file:text-blue-700 hover:file:bg-blue-100"
              />
              {selectedFile && (
                <p className="mt-2 text-sm text-slate-600">
                  Loaded: <span className="font-medium">{selectedFile}</span> (
                  {fileData.length} pairs)
                </p>
              )}
            </div>

            {fileData.length > 0 && (
              <div className="text-black min-w-[200px]">
                <label className="block text-sm font-medium text-slate-700 mb-2">
                  Select Pair (1-{fileData.length})
                </label>
                <select
                  value={selectedPairIndex}
                  onChange={(e) => {
                    const idx = parseInt(e.target.value);
                    setSelectedPairIndex(idx);
                    setNum1(fileData[idx].a.toString());
                    setNum2(fileData[idx].b.toString());
                  }}
                  className="w-full px-4 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500"
                >
                  {fileData.map((pair, idx) => (
                    <option key={idx} value={idx}>
                      Pair {idx + 1}: {pair.a} × {pair.b}
                    </option>
                  ))}
                </select>
              </div>
            )}
          </div>
        </div>

        {/* Input Controls */}
        <div className="bg-white  text-black rounded-lg shadow-lg p-6 mb-6">
          <div className="flex gap-4 items-end flex-wrap">
            <div className="flex-1   min-w-[200px]">
              <label className="block text-sm font-medium mb-2">Number 1</label>
              <input
                type="text"
                value={num1}
                onChange={(e) => setNum1(e.target.value.replace(/[^0-9]/g, ""))}
                className="w-full px-4 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500"
                placeholder="Enter first number"
              />
            </div>
            <div className="flex-1 min-w-[200px]">
              <label className="block text-sm font-medium text-slate-700 mb-2">
                Number 2
              </label>
              <input
                type="text"
                value={num2}
                onChange={(e) => setNum2(e.target.value.replace(/[^0-9]/g, ""))}
                className="w-full px-4 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500"
                placeholder="Enter second number"
              />
            </div>
            <button
              onClick={executeAlgorithm}
              className="px-6 py-2 bg-blue-600 text-white rounded-lg hover:bg-blue-700 transition-colors font-medium"
            >
              Calculate
            </button>
          </div>
        </div>

        {/* Playback Controls */}
        {steps.length > 0 && (
          <div className="bg-white rounded-lg shadow-lg p-6 mb-6">
            <div className="flex items-center gap-4 mb-4">
              <button
                onClick={() => setIsPlaying(!isPlaying)}
                className="p-2 bg-blue-600 text-white rounded-lg hover:bg-blue-700 transition-colors"
              >
                {isPlaying ? <Pause size={20} /> : <Play size={20} />}
              </button>
              <button
                onClick={() =>
                  setCurrentStep(Math.min(currentStep + 1, steps.length - 1))
                }
                disabled={currentStep >= steps.length - 1}
                className="p-2 bg-slate-600 text-white rounded-lg hover:bg-slate-700 transition-colors disabled:opacity-50"
              >
                <SkipForward size={20} />
              </button>
              <button
                onClick={() => {
                  setCurrentStep(0);
                  setIsPlaying(false);
                }}
                className="p-2 bg-slate-600 text-white rounded-lg hover:bg-slate-700 transition-colors"
              >
                <RotateCcw size={20} />
              </button>
              <div className="flex-1">
                <input
                  type="range"
                  min="0"
                  max={steps.length - 1}
                  value={currentStep}
                  onChange={(e) => setCurrentStep(parseInt(e.target.value))}
                  className="w-full"
                />
              </div>
              <span className="text-sm font-medium text-slate-600">
                Step {currentStep + 1} / {steps.length}
              </span>
            </div>

            {/* Current Step Info */}
            <div className="bg-slate-50 rounded-lg p-4">
              <h3 className="font-semibold text-slate-800 mb-2">
                Current Operation: {steps[currentStep].x} ×{" "}
                {steps[currentStep].y}
              </h3>
              <div className="space-y-1">
                {steps[currentStep].operations.map((op, idx) => (
                  <p key={idx} className="text-sm text-slate-600">
                    • {op}
                  </p>
                ))}
              </div>
              {steps[currentStep].result !== null && (
                <p className="mt-3 text-lg font-bold text-green-600">
                  Result: {steps[currentStep].result}
                </p>
              )}
            </div>
          </div>
        )}

        {/* Recursion Tree */}
        {tree && (
          <div className="bg-white rounded-lg shadow-lg p-6">
            <h2 className="text-xl font-bold text-slate-800 mb-4">
              Recursion Tree
            </h2>
            <div className="overflow-auto">
              <svg width="800" height={svgHeight} className="mx-auto">
                {renderTree(tree)}
              </svg>
            </div>
            <div className="mt-4 flex gap-6 justify-center text-sm">
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-blue-500 rounded"></div>
                <span className="text-slate-600">Current Step</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-green-500 rounded"></div>
                <span className="text-slate-600">Completed</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-slate-200 rounded border border-slate-400"></div>
                <span className="text-slate-600">Pending</span>
              </div>
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default KaratsubaVisualizer;