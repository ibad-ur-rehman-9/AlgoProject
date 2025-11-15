"use client"

import { useState } from "react"

export default function KaratsubaVisualizer(){
    const [num1, setNum1] = useState("")
    const [num2, setNum2] = useState("");
    const steps = []; // simple array
    const executeAlgoithm = () => {
          console.log("Running Karatsuba...");
    }
    function karatsuba(a,b){
        steps.push({a,b, action: "start"});
        if(a < 10 || b < 10){
            steps.push({ a, b, action: "base", result: a * b });
            return a*b;
        }
        steps.push({ a, b, action: "split" });
        const m = Math.max(a.toString().length, b.toString().length);
        const n = Math.floor(m / 2);
        const p = 10 ** n;

        const high1 = Math.floor(a / p);
        const low1 = Math.floor(a % p);
        const high2 = Math.floor(b / p);
        const low2 = Math.floor(b % p);

        const z2 = karatsuba(high1,high2); // higher bits pe lagegi k ki power
        const z0 = karatsuba(low1, low2);
        const z1 = karatsuba(high1 + low1, high2 + low2) - z2 - z0;
        steps.push({ a, b, action: "end", result });
        return z2*p*p + z1*p + z0;

    }
    return (
      <div>
        <div className="bg-white rounded-lg shadow-lg p-6 mb-6">
          <div className="flex gap-4 items-end flex-wrap">
            <div className="flex-1 min-w-[200px]">
              <label className="block text-sm font-medium text-slate-700 mb-2">
                Number 1
              </label>
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
              onClick={executeAlgoithm}
              className="px-6 py-2 bg-blue-600 text-white rounded-lg hover:bg-blue-700 transition-colors font-medium"
            >
              Calculate
            </button>
          </div>
        </div>
      </div>
    );
}