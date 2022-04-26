import {Component} from "./geometry.js";
import {SVG_Controller} from "./svg controller.js";

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
        
        if (side == "front" || side == "single") {
            this.svg.style.transform = "rotateX(180deg)";
        } else if (side == "back") {
            this.svg.style.transform = "rotateZ(180deg)";
        }

        this.drawGrid();
        this.drawBoundary();
        this.drawPlacement();
        document.getElementById('Layout_'+this.side).appendChild(this.svg);
    }

    drawGrid() {
        let i, j;
        i = -100;
        for (j = -100; j < 100; j++) {this.create2DLine({"polyline":`${i}, ${j} ${i+200}, ${j}`, stroke_width: 0.01});}
        j = -100;
        for (i = -100; i < 100; i++) {this.create2DLine({"polyline":`${i}, ${j} ${i}, ${j+200}`, stroke_width: 0.01});}
    }

    drawBoundary() {
        this.create2DPolygon({
            "polygon":`${this.margin_x + 2}, ${this.margin_y + 0} 
                       ${this.margin_x + this.width}, ${this.margin_y + 0} 
                       ${this.margin_x + this.width}, ${this.margin_y + this.height} 
                       ${this.margin_x + 0}, ${this.margin_y + this.height} 
                       ${this.margin_x + 0}, ${this.margin_y + 9} 
                       ${this.margin_x + 2}, ${this.margin_y + 9}`,
            "stroke_alignment": "outer",
            "stroke_width": 1,
        });
    }

    drawPlacement() {
        let comp_id;
        let placement_data = this.placement_data;
        let stack = [];
        
        if (this.side == "front") {comp_id = "F_RootHole";}
        else if (this.side == "back") {comp_id = "B_RootHole";}
        else {comp_id = "Origin";}

        stack.push(placement_data[comp_id]["leftChild"]);
        stack.push(placement_data[comp_id]["rightChild"]);
        while (stack.length != 0) {
            comp_id = stack.pop();
            if (comp_id == "null") {continue;}
            placement_data[comp_id]["side"] = this.side;
            this.create2DGeometry({"component": placement_data[comp_id], "fill": placement_data[comp_id]["color"]});
            this.createText({"component": placement_data[comp_id]});
            // console.log(comp_id);
            this.drawPin(comp_id);
            stack.push(placement_data[comp_id]["leftChild"]);
            stack.push(placement_data[comp_id]["rightChild"]);
        }
    }

    drawPin(name) {
        console.log(this.pin_data[name]);
        for (let [key, value] of Object.entries(this.pin_data[name])) {
            this.create2DGeometry({"component": this.pin_data[name][key], "stroke_width": 0, "alignment": "center", "fill": "#111111"});
            // this.createText({"component": this.pin_data[name][key], "name": this.pin_data[name][key]["name"]}); /*.slice(-1)*/
        }
    }

    create2DPolygon({polygon, stroke="#666666", stroke_width=0}) {
        let poly = document.createElementNS("http://www.w3.org/2000/svg", 'polygon');
        poly.setAttribute('points', polygon);
        poly.setAttribute('fill', "none");
        poly.style['stroke'] = "#197531";
        poly.style['stroke-width'] = stroke_width;
        this.svg.appendChild(poly);
    }

    create2DGeometry({component, alignment="bottom_left", stroke_alignment="center", stroke="#666666", stroke_width=0, fill="#666666"}) {
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
        rect.setAttribute('fill', fill);
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