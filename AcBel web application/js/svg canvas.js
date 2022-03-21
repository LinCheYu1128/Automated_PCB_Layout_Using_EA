import {Component} from "./geometry.js";
import {SVG_Controller} from "./svg controller.js";

let T501_information;

export class Canvas {
    constructor(side, data) {
        this.placement_data = data["placement_data"];
        this.pin_data = data["pin_data"];
        this.net_data = data["net_data"];
        this.side = side;
        this.width = 29.2;
        this.height = 32.5;
        this.margin_x = 5,
        this.margin_y = 5,
        this.svg_controller = new SVG_Controller(this.width, this.height, this.margin_x, this.margin_y);
        this.svg = this.svg_controller.svg;
        
        // this.svg.style.transform = "rotateX(180deg)";
        if (side == "front" || side == "single") {
            this.svg.style.transform = "rotateX(180deg)";
        } else if (side == "back") {
            this.svg.style.transform = "rotateZ(180deg)";
        }

        document.getElementById('Layout_'+this.side).appendChild(this.svg);
        this.drawGrid();
        this.create2DGeometry({
            "polygon":`${this.margin_x + 2}, ${this.margin_y + 0} 
                       ${this.margin_x + this.width}, ${this.margin_y + 0} 
                       ${this.margin_x + this.width}, ${this.margin_y + this.height} 
                       ${this.margin_x + 0}, ${this.margin_y + this.height} 
                       ${this.margin_x + 0}, ${this.margin_y + 9} 
                       ${this.margin_x + 2}, ${this.margin_y + 9}`,
            "stroke_alignment": "outer",
            "stroke_width": 1,
        });
        this.drawPlacement();
    }

    drawGrid() {
        let i, j;
        i = 0;
        for (j = -50; j < 50; j++) {this.create2DLine({"polyline":`${i}, ${j} ${i+50}, ${j}`, stroke_width: 0.01});}
        j = 0;
        for (i = -50; i < 50; i++) {this.create2DLine({"polyline":`${i}, ${j} ${i}, ${j+50}`, stroke_width: 0.01});}
    }

    // drawPlacement() {
    //     console.log(this.placement_data);
    //     for (let [key, value] of Object.entries(this.placement_data)) {
    //         this.create2DGeometry({"component": this.placement_data[key]});
    //         this.createText({"component": this.placement_data[key]});
    //         // this.grid.addObstacle(this.placement_data[key]["size"], this.placement_data[key]["position"]);
    //     }
    // }

    drawPlacement() {
        let name;
        let stack = [];
        let placement_data = this.placement_data;

        if (this.side == "front") {name = "F_RootHole";}
        else if (this.side == "back") {name = "B_RootHole";}
        else {name = "Origin";}

        stack.push(placement_data[name]["leftChild"]);
        stack.push(placement_data[name]["rightChild"]);
        while (stack.length != 0) {
            name = stack.pop();
            if (name == "null") {continue;}
            this.create2DGeometry({"component": placement_data[name]});
            this.createText({"component": placement_data[name]});
            stack.push(placement_data[name]["leftChild"]);
            stack.push(placement_data[name]["rightChild"]);
        }
    }

    create2DGeometry({component, alignment="bottom_left", stroke_alignment="center", stroke_width=0, polygon=null}) {
        if (polygon) {
            let poly = document.createElementNS("http://www.w3.org/2000/svg", 'polygon');
            poly.setAttribute('points', polygon);
            poly.setAttribute('fill', "none");
            poly.style['stroke'] = "0x197531".replace("0x", "#");
            poly.style['stroke-width'] = stroke_width;
            this.svg.appendChild(poly);
            return;
        }
        let rect = document.createElementNS("http://www.w3.org/2000/svg", 'rect');
        let stroke_alignment_ratio;
        if (stroke_alignment == "inner") {
            stroke_alignment_ratio = 0;
        } else if (stroke_alignment == "center") {
            stroke_alignment_ratio = 0.5;
        } else if (stroke_alignment == "outer") {
            stroke_alignment_ratio = 1;
        }
        if (alignment == "bottom_left") {
            rect.setAttribute('x', this.margin_x + component["margin"] + component["position"][0] - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('y', this.margin_y + component["margin"] + component["position"][1] - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('width', component["size"][0]-2*component["margin"] + 2*stroke_width*stroke_alignment_ratio);
            rect.setAttribute('height', component["size"][1]-2*component["margin"] + 2*stroke_width*stroke_alignment_ratio);
        } else if (alignment == "center") {
            rect.setAttribute('x', this.margin_x + component["margin"] + (component["position"][0] - component["size"][0]/2) - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('y', this.margin_y + component["margin"] + (component["position"][1] - component["size"][1]/2) - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('width', component["size"][0]-2*component["margin"] + 2*stroke_width*stroke_alignment_ratio);
            rect.setAttribute('height', component["size"][1]-2*component["margin"] + 2*stroke_width*stroke_alignment_ratio);
        }
        rect.setAttribute('fill', component["color"]);
        rect.style['stroke'] = component["border_color"];
        rect.style['stroke-width'] = stroke_width;
        this.svg.appendChild(rect);
    }

    create2DLine({polyline, stroke="#666666", stroke_width=0.2}) {
        let poly = document.createElementNS("http://www.w3.org/2000/svg", 'polyline');
        poly.setAttribute('points', polyline);
        poly.setAttribute('fill', "none");
        poly.style['stroke'] = stroke;
        poly.style['stroke-width'] = stroke_width;
        this.svg.appendChild(poly);
        return;
    }

    createText({component}) {
        let text = document.createElementNS("http://www.w3.org/2000/svg", 'text');
        text.setAttribute('x', this.margin_x + (component["position"][0] + component["size"][0]/2));
        text.setAttribute('y', this.margin_y + (component["position"][1] + component["size"][1]/2));
        text.style['font'] = "0.5px \"Lato\", sans-serif";
        text.style['dominant-baseline'] = "middle";
        text.style['text-anchor'] = "middle";
        text.textContent = component.name;
        let x = this.margin_x + (component["position"][0] + component["size"][0]/2);
        let y = this.margin_y + (component["position"][1] + component["size"][1]/2);
        if (this.side == "front" || this.side == "single") {
            text.setAttribute('transform', `translate(${x}, ${y}) scale(1, -1) translate(${-x}, ${-y})`);
        } else {
            text.setAttribute('transform', `translate(${x}, ${y}) rotate(180) translate(${-x}, ${-y})`);
        }
        this.svg.appendChild(text);
    }
}