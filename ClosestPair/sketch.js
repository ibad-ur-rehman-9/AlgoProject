let points = [];
let actions = [];
let closestPair = { p1: null, p2: null };
let step = 0;
let canvasSize = 800;
let minDist = Infinity;
let stepBtn, playBtn, pauseBtn, prevBtn;
let currentFile = "points1.json"; // default file
let fileSelector;

// First to run
function preload() {
  // Initial load of default file
  loadJSON(currentFile, (data) => {
    points = data.points;
  });
}

// Second to run
function setup() {
  let canvas = createCanvas(1080, 720);
  canvas.parent('canvas-container');
  frameRate(2);

  // Get the file selector from HTML
  fileSelector = select('#fileSelect');
  fileSelector.changed(loadNewFile);

  normalizeAndInitialize();

  noLoop();

  // Button container
  let buttonContainer = createDiv();
  buttonContainer.style("position", "absolute");
  buttonContainer.style("bottom", "10px");
  buttonContainer.style("left", "50%");
  buttonContainer.style("transform", "translateX(-50%)");
  buttonContainer.style("display", "flex");
  buttonContainer.style("gap", "10px");

  prevBtn = createButton("Previous");
  prevBtn.parent(buttonContainer);
  prevBtn.mousePressed(prevStep);

  stepBtn = createButton("Next Step");
  stepBtn.parent(buttonContainer);
  stepBtn.mousePressed(nextStep);

  let resetBtn = createButton("Reset");
  resetBtn.parent(buttonContainer);
  resetBtn.mousePressed(resetVisualization);
}

function normalizeAndInitialize() {
  if (!points || points.length === 0) return;

  // Normalization of points to fit the canvas
  let maxX = Math.max(...points.map((p) => p.x));
  let maxY = Math.max(...points.map((p) => p.y));

  for (let p of points) {
    p.x = (p.x / maxX) * (width - 100) + 50;
    p.y = (p.y / maxY) * (height - 100) + 50;
  }

  // Reset and run algorithm
  actions = [];
  step = 0;
  minDist = Infinity;
  closestPair = { p1: null, p2: null };

  points.sort((a, b) => a.x - b.x);
  DC(points);

  redraw();
}

function loadNewFile() {
  currentFile = fileSelector.value();

  // Load new file
  loadJSON(currentFile, (data) => {
    points = data.points;
    normalizeAndInitialize();
  });
}

function resetVisualization() {
  step = 0;
  redraw();
}

function draw() {
  background(240);

  if (!points || points.length === 0) return;

  // Draw all points
  fill(200);
  noStroke();
  for (let p of points) {
    ellipse(p.x, p.y, 10, 10);
  }

  // Animate steps
  if (step < actions.length) {
    let act = actions[step];

    if (act.type === "compare") {
      stroke("orange");
      line(act.p1.x, act.p1.y, act.p2.x, act.p2.y);
    }

    if (act.type == "midpoint") {
      fill("purple");
      ellipse(act.p.x, act.p.y, 10, 10);
    }

    if (act.type == "consideredPointsLeft") {
      noStroke();
      fill(255, 0, 0, 50);
      let xs = act.ps.map((p) => p.x);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      rect(minX - 5, 0, maxX - minX + 10, height);

      fill(255, 0, 0);
      for (let p of act.ps) {
        ellipse(p.x, p.y, 10, 10);
      }
    }

    if (act.type == "consideredPointsRight") {
      noStroke();
      fill(0, 255, 0, 100);
      let xs = act.ps.map((p) => p.x);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      rect(minX - 5, 0, maxX - minX + 10, height);

      fill("green");
      for (let p of act.ps) {
        ellipse(p.x, p.y, 10, 10);
      }
    }

    if (act.type == "consideredPointsAll") {
      noStroke();
      fill(255, 0, 0, 50);
      let xs = act.left.map((p) => p.x);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      rect(minX - 5, 0, maxX - minX + 10, height);

      fill(0, 255, 0, 100);
      let xs1 = act.right.map((p) => p.x);
      let minX1 = Math.min(...xs1);
      let maxX1 = Math.max(...xs1);
      rect(minX1 - 5, 0, maxX1 - minX1 + 10, height);
    }

    if (act.type === "consideredPointsStrip") {
      fill(100, 100, 255, 150);
      noStroke();
      let xs = act.ps.map((p) => p.x);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      rect(minX - 5, 0, maxX - minX + 10, height);

      fill("black");
      for (let p of act.ps) {
        ellipse(p.x, p.y, 10, 10);
      }

      noStroke();
      fill(255, 0, 0, 50);
      let xs2 = act.left.map((p) => p.x);
      let minX2 = Math.min(...xs2);
      let maxX2 = Math.max(...xs2);
      rect(minX2 - 5, 0, maxX2 - minX2 + 10, height);

      fill(0, 255, 0, 100);
      let xs1 = act.right.map((p) => p.x);
      let minX1 = Math.min(...xs1);
      let maxX1 = Math.max(...xs1);
      rect(minX1 - 5, 0, maxX1 - minX1 + 10, height);
    }

    if (act.type === "split") {
      stroke("blue");
      strokeWeight(2);
      line(act.x, 0, act.x, height);
    }

    if (act.type === "closestUpdate") {
      stroke("red");
      strokeWeight(3);
      line(act.p1.x, act.p1.y, act.p2.x, act.p2.y);
    }

    fill(0);
    noStroke();
    textSize(20);
    let msg = getStepMessage(act);
    text(msg, 10, height - 20);

    // Show step counter
    textSize(16);
    text(`Step ${step + 1} of ${actions.length}`, 10, 30);
  } else if (actions.length > 0) {
    // Show final result
    fill(0);
    noStroke();
    textSize(20);
    text(`Algorithm complete! Closest distance: ${minDist.toFixed(2)}`, 10, height - 20);

    // Draw final closest pair
    if (closestPair.p1 && closestPair.p2) {
      stroke("red");
      strokeWeight(3);
      line(closestPair.p1.x, closestPair.p1.y, closestPair.p2.x, closestPair.p2.y);
    }
  }
}

function nextStep() {
  if (step < actions.length - 1) step++;
  redraw();
}

function prevStep() {
  if (step > 0) step--;
  redraw();
}

function DC(arr) {
  if (arr.length <= 3) {
    let localMin = Infinity;
    for (let i = 0; i < arr.length; i++) {
      for (let j = i + 1; j < arr.length; j++) {
        actions.push({ type: "compare", p1: arr[i], p2: arr[j] });
        let d = distance(arr[i], arr[j]);
        if (d < localMin) localMin = d;
        if (d < minDist) {
          minDist = d;
          closestPair = { p1: arr[i], p2: arr[j] };
          actions.push({ type: "closestUpdate", p1: arr[i], p2: arr[j] });
        }
      }
    }
    return localMin;
  }

  let mid = Math.floor(arr.length / 2);
  let midpoint = arr[mid];
  actions.push({ type: "midpoint", p: midpoint });

  let left = arr.slice(0, mid);
  let right = arr.slice(mid);

  actions.push({ type: "split", x: midpoint.x });
  actions.push({ type: "consideredPointsLeft", ps: left });
  let dl = DC(left);

  actions.push({ type: "consideredPointsRight", ps: right });
  let dr = DC(right);

  actions.push({ type: "consideredPointsAll", left: left, right: right });

  let d = Math.min(dl, dr);
  actions.push({ type: "stripInit", midpoint: midpoint, dist: d });

  let strip = [];
  for (let p of arr) {
    if (Math.abs(p.x - midpoint.x) < d) {
      strip.push(p);
      actions.push({ type: "compare", p1: p, p2: midpoint });
    }
  }

  actions.push({ type: "consideredPointsStrip", ps: strip, left: left, right: right });

  strip.sort((a, b) => a.y - b.y);

  for (let i = 0; i < strip.length; i++) {
    for (let j = i + 1; j < strip.length && strip[j].y - strip[i].y < d; j++) {
      actions.push({ type: "compare", p1: strip[i], p2: strip[j] });
      let dist = distance(strip[i], strip[j]);
      if (dist < minDist) {
        minDist = dist;
        closestPair = { p1: strip[i], p2: strip[j] };
        actions.push({ type: "closestUpdate", p1: strip[i], p2: strip[j] });
      }
      if (dist < d) d = dist;
    }
  }

  return d;
}

function distance(a, b) {
  return Math.sqrt((a.x - b.x) ** 2 + (a.y - b.y) ** 2);
}

function getStepMessage(act) {
  switch (act.type) {
    case "compare":
      return `Comparing points (${act.p1.x.toFixed(1)}, ${act.p1.y.toFixed(1)}) and (${act.p2.x.toFixed(1)}, ${act.p2.y.toFixed(1)})`;
    case "midpoint":
      return `Midpoint chosen at (${act.p.x.toFixed(1)}, ${act.p.y.toFixed(1)})`;
    case "split":
      return `Splitting at x = ${act.x.toFixed(1)}`;
    case "consideredPointsLeft":
      return `Considering left subset of ${act.ps.length} points`;
    case "consideredPointsRight":
      return `Considering right subset of ${act.ps.length} points`;
    case "consideredPointsAll":
      return `Merging left and right subsets`;
    case "consideredPointsStrip":
      return `Points in strip: ${act.ps.length}`;
    case "closestUpdate":
      return `Updating closest pair distance to ${minDist.toFixed(2)}`;
    case "stripInit":
      return `Initializing strip, d = ${act.dist.toFixed(2)}`;
    default:
      return act.type;
  }
}