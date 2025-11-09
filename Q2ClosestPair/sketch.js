let points = []; // will load from json
let actions = []; // stored during our DC calculation
let closestPair = { p1: null, p2: null };
let step = 0;
let canvasSize = 800;
let minDist = Infinity;
let stepBtn, playBtn, pauseBtn, prevBtn;

// First to run
function preload() {
  // loadJSON returns an object asynchronously, so use a callback
  loadJSON("points.json", (data) => {
    points = data.points; // expects { "points": [ {x:..., y:...}, ... ] }
  });

  // Asynchronous objects? basically loadJson is an asynchronous function,
  // asynchronous functions take a while to run, but they dont block the rest of the code

  // Example of asynchronous behavior
  // console.log("A");
  // setTimeout(() => console.log("B"), 2000);
  // console.log("C");

  // Output:
  // A;
  // C; -> rest of the code didnt block, the async setTimeout takes time but allows other execution
  // B;

  // However ours is special case, we dont want the code to run till json fetch is complete, so we use preload
  // preload() is special: p5.js waits for all async loads inside preload() to finish before running setup().
}

// Second to run
function setup() {
  createCanvas(1080, 720);
  frameRate(2); // default: 60 times per second unless you change frameRate()
  // normalization of points to fit the canvas
  let maxX = Math.max(...points.map((p) => p.x));
  let maxY = Math.max(...points.map((p) => p.y));

  for (let p of points) {
    p.x = (p.x / maxX) * (width - 50); // leave some margin
    p.y = (p.y / maxY) * (height - 50);
  }
  noLoop();
  // a container for buttons
  let buttonContainer = createDiv();
  buttonContainer.style("position", "absolute");
  buttonContainer.style("bottom", "10px"); // 10px from bottom
  buttonContainer.style("left", "50%");
  buttonContainer.style("transform", "translateX(-50%)"); // center horizontally
  buttonContainer.style("display", "flex");
  buttonContainer.style("gap", "10px"); // spacing between buttons

  // Create buttons and attach them to container
  
  prevBtn = createButton("Previous");
  prevBtn.parent(buttonContainer);
  prevBtn.mousePressed(prevStep);
  stepBtn = createButton("Next Step");
  stepBtn.parent(buttonContainer);
  stepBtn.mousePressed(nextStep);


  
}

// Draw is the main animation loop — everything you draw goes here. and it runs continously after the setup
// also it is called every 0.5 seconds(framerate is 2) automatically so we need to add checks like:
// if points zero return, if actions = 0 only then run dc, dont just keep run dc on every draw

function draw() {
  background(240);

  // Wait until JSON is loaded, if no points then don't go further
  if (!points || points.length === 0) return;

  // Draw all points

  // Run algorithm once (only after points are loaded)
  if (actions.length === 0) {
    points.sort((a, b) => a.x - b.x);
    DC(points);
  }
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
      fill(255, 0, 0, 50); // semi-transparent red
      // get min/max x and y
      let xs = act.ps.map((p) => p.x);
      let ys = act.ps.map((p) => p.y);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      let minY = 0;
      let maxY = height;

      rect(minX - 5, minY - 5, maxX - minX + 10, maxY - minY + 10);

      // then draw points on top
      fill(255, 0, 0);
      for (let p of act.ps) {
        ellipse(p.x, p.y, 10, 10);
      }
    }
    if (act.type == "consideredPointsRight") {
      noStroke();
      fill(0, 255, 0, 100); // semi-transparent green
      // get min/max x and y
      let xs = act.ps.map((p) => p.x);
      let ys = act.ps.map((p) => p.y);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      let minY = 0;
      let maxY = height;

      rect(minX - 5, minY - 5, maxX - minX + 10, maxY - minY + 10);

      // then draw points on top
      fill("green");
      for (let p of act.ps) {
        ellipse(p.x, p.y, 10, 10);
      }
    }
    if (act.type == "consideredPointsAll") {
      noStroke();
      fill(255, 0, 0, 50); // semi-transparent red
      // get min/max x and y
      let xs = act.left.map((p) => p.x);
      let ys = act.left.map((p) => p.y);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      let minY = 0;
      let maxY = height;

      rect(minX - 5, minY - 5, maxX - minX + 10, maxY - minY + 10);
      fill(0, 255, 0, 100); // semi-transparent green

      let xs1 = act.right.map((p) => p.x);
      let ys1 = act.right.map((p) => p.y);
      let minX1 = Math.min(...xs1);
      let maxX1 = Math.max(...xs1);
      let minY1 = 0;
      let maxY1 = height;

      rect(minX1 - 5, minY1 - 5, maxX1 - minX1 + 10, maxY - minY1 + 10);
    }
    if (act.type === "consideredPointsStrip") {
      fill(100, 100, 255, 150); // stronger blue
      noStroke();

      // get min/max x and y
      let xs = act.ps.map((p) => p.x);
      let ys = act.ps.map((p) => p.y);
      let minX = Math.min(...xs);
      let maxX = Math.max(...xs);
      let minY = 0;
      let maxY = height;

      rect(minX - 5, minY - 5, maxX - minX + 10, maxY - minY + 10);

      // then draw points on top
      fill("black");
      for (let p of act.ps) {
        ellipse(p.x, p.y, 10, 10);
      }
      noStroke();
      fill(255, 0, 0, 50); // semi-transparent red
      // get min/max x and y
      let xs2 = act.left.map((p) => p.x);
      let ys2 = act.left.map((p) => p.y);
      let minX2 = Math.min(...xs2);
      let maxX2 = Math.max(...xs2);
      let minY2 = 0;
      let maxY2 = height;

      rect(minX2 - 5, minY2 - 5, maxX2 - minX2 + 10, maxY2 - minY2 + 10);
      fill(0, 255, 0, 100); // semi-transparent green

      let xs1 = act.right.map((p) => p.x);
      let ys1 = act.right.map((p) => p.y);
      let minX1 = Math.min(...xs1);
      let maxX1 = Math.max(...xs1);
      let minY1 = 0;
      let maxY1 = height;

      rect(minX1 - 5, minY1 - 5, maxX1 - minX1 + 10, maxY - minY1 + 10);
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
    text(msg, 10, height - 20); // bottom left corner
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
  // baze caze
  if (arr.length <= 3) {
    let localMin = Infinity; // local minimum for this subarray
    for (let i = 0; i < arr.length; i++) {
      for (let j = i + 1; j < arr.length; j++) {
        actions.push({ type: "compare", p1: arr[i], p2: arr[j] });
        let d = distance(arr[i], arr[j]);
        if (d < localMin) localMin = d; // update local minimum
        if (d < minDist) {
          minDist = d;
          closestPair = { p1: arr[i], p2: arr[j] };
          actions.push({ type: "closestUpdate", p1: arr[i], p2: arr[j] });
        }
      }
    }
    return localMin; // return local min
  }

  // Sorting was done in setup part

  // Now we split into two
  // let mid = points.length()/2;
  let mid = Math.floor(arr.length / 2);

  let midpoint = arr[mid];
  actions.push({ type: "midpoint", p: midpoint });

  let left = arr.slice(0, mid); // from index 0 to mid-1
  let right = arr.slice(mid); // from index mid to end
  actions.push({ type: "split", x: midpoint.x });

  actions.push({ type: "consideredPointsLeft", ps: left });
  let dl = DC(left);
  console.log("dl: ", dl);

  actions.push({ type: "consideredPointsRight", ps: right });
  let dr = DC(right);
  console.log("dr: ", dr);
  actions.push({ type: "consideredPointsAll", left: left, right: right });

  // theoretical strip width
  let d = min(dl, dr);
  console.log("d: ", d);

  actions.push({ type: "stripInit", midpoint: midpoint, dist: d });
  let strip = [];
  for (let p of arr) {
    if (Math.abs(p.x - midpoint.x) < d) {
      strip.push(p);
      actions.push({ type: "compare", p1: p, p2: midpoint });
    }
  }
  actions.push({ type: "consideredPointsStrip", ps: strip, left:left, right:right }); // points inside strip

  // Compare points in strip (next up to 7 points)
  for (let i = 0; i < strip.length; i++) {
    for (let j = i + 1; j < strip.length && strip[j].y - strip[i].y < d; j++) {
      actions.push({ type: "compare", p1: strip[i], p2: strip[j] });
      let dist = distance(strip[i], strip[j]);
      if (dist < minDist) {
        minDist = dist;
        closestPair = { p1: strip[i], p2: strip[j] };
        actions.push({ type: "closestUpdate", p1: strip[i], p2: strip[j] });
      }
      // Update local d for this recursion
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
      return `Comparing points (${act.p1.x.toFixed(1)}, ${act.p1.y.toFixed(
        1
      )}) and (${act.p2.x.toFixed(1)}, ${act.p2.y.toFixed(1)})`;
    case "midpoint":
      return `Midpoint chosen at (${act.p.x.toFixed(1)}, ${act.p.y.toFixed(
        1
      )})`;
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
      return `Updating closest pair distance`;
    case "stripInit":
      return `Initializing strip, d = ${act.dist.toFixed(2)}`;
    default:
      return act.type;
  }
}