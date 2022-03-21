import {Component} from "./geometry.js";
import {Canvas} from "./svg canvas.js";

for (let i = 0; i < 30; i++) {
    let front_layout = new Canvas({"side": "front", "width": 29.2, "height": 32.5});
    let back_layout = new Canvas({"side": "back", "width": 29.2, "height": 32.5});
    
    front_layout.importComponent(i);
    back_layout.importComponent(i);
}

// let A = new Component({"size": {"x": 5, "y": 3}, "position": {"x": 5, "y": 5}, "color": "0xFF0000"});
// let B = new Component({"size": {"x": 5, "y": 8}, "position": {"x": 10, "y": 13}, "color": "0xDD0000"});
// let C = new Component({"size": {"x": 10, "y": 10}, "position": {"x": 15, "y": 15}, "color": "0xFF0088"});

// front_layout.create2DGeometry({"component": A, "stroke_alignment": "inner"})
// front_layout.create2DGeometry({"component": B, "alignment": "center", "stroke_alignment": "inner"})
// front_layout.create2DGeometry({"component": C, "stroke_alignment": "outer"})