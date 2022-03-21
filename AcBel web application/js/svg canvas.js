import {Component} from "./geometry.js";
import {SVG_Controller} from "./svg controller.js";

let T501_information;

export class Canvas {
    constructor(side, data) {
        this.data = data;
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
        this.create2DGeometry({
            "polygon":`${this.margin_x + 2}, ${this.margin_y + 0} ${this.margin_x + 29.2},
                       ${this.margin_y + 0} ${this.margin_x + 29.2},
                       ${this.margin_y + 32.5} ${this.margin_x + 0},
                       ${this.margin_y + 32.5} ${this.margin_x + 0},
                       ${this.margin_y + 9} ${this.margin_x + 2},
                       ${this.margin_y + 9}`,
                       "stroke_alignment": "inner",
                       "stroke_width": 0.5
        });
        this.drawComponent();
    }

    drawComponent() {
        let name;
        let stack = [];

        if (this.side == "front") {name = "F_RootHole";}
        else if (this.side == "back") {name = "B_RootHole";}
        else {name = "Origin";}

        stack.push(this.data[name]["leftChild"]);
        stack.push(this.data[name]["rightChild"]);
        while (stack.length != 0) {
            name = stack.pop();
            if (name == "null") {continue;}
            this.create2DGeometry({"component": this.data[name]});
            this.createText({"component": this.data[name]});
            stack.push(this.data[name]["leftChild"]);
            stack.push(this.data[name]["rightChild"]);
        }
    }

    importComponent(num) {
        let T501_side;
        let early_break = false;
        let data, contour;

        if (this.side == "front") {
            data = front_data;
            contour = front_horizon_contour[num];
        } else if (this.side == "back") {
            data = back_data;
            contour = back_horizon_contour[num];
        }
    
        for (let t = 0; t < Object.keys(data).length; t++) {
            if (t-1 == num) {
                early_break = true;
                break;
            }
            let i = Object.keys(data)[t];
            console.log("i", i)
            // if (i == "F_RootHole" || i == "B_RootHole") {
            //     continue;
            // }
            let C = new Component({"size": {"x": data[i]["size"][0], "y": data[i]["size"][1]}, "position": {"x": data[i]["position"][0], "y": data[i]["position"][1]}, "color": data[i]["color"]});
            this.create2DGeometry({"component": C})
        }
        
        // draw T501 pin
        for (let i in front_data) {
            if (i == "T501") {
                T501_side = "front";
                T501_information = JSON.parse(JSON.stringify(front_data[i]));
            }
        }
        for (let i in back_data) {
            if (i == "T501") {
                T501_side = "back";
                T501_information = JSON.parse(JSON.stringify(back_data[i]));
            }
        }

        if (this.side !== T501_side) {
            for (let k = 0; k <= 11; k++) {
                let pin_position = T501_information["pin position"][k];
                let pin_color = T501_information["color"];
                if (k == 0 || k == 1 || k == 4 || k == 5 || k ==6 || k == 7 || k == 8) {
                    let pin_component = new Component({"size": {"x": 2, "y": 2}, "position": {"x": pin_position[0], "y": pin_position[1]}, "color": pin_color});
                    this.create2DGeometry({"component": pin_component, "alignment": "center"});
                }
            }
        }
        let total_string = "";
        for (let i in contour) {
            let string = "";
            let k = parseInt(i);
            // draw vertical line
            if (k < Object.keys(contour).length - 1) {
            }
            string += `${this.margin_x + contour[k]["begin"][0]}, ${this.margin_y + contour[k]["begin"][1]} ${this.margin_x + contour[k]["end"][0]}, ${this.margin_y + contour[k]["end"][1]}`;
            string += " ";
            total_string += string;
        }
        this.create2DLine({"polyline": total_string})
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
            rect.setAttribute('x', this.margin_x + component["position"][0] - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('y', this.margin_y + component["position"][1] - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('width', component["size"][0] + 2*stroke_width*stroke_alignment_ratio);
            rect.setAttribute('height', component["size"][1] + 2*stroke_width*stroke_alignment_ratio);
        } else if (alignment == "center") {
            rect.setAttribute('x', this.margin_x + (component["position"][0] - component["size"][0]/2) - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('y', this.margin_y + (component["position"][1] - component["size"][1]/2) - stroke_width*stroke_alignment_ratio);
            rect.setAttribute('width', component["size"][0] + 2*stroke_width*stroke_alignment_ratio);
            rect.setAttribute('height', component["size"][1] + 2*stroke_width*stroke_alignment_ratio);
        }
        rect.setAttribute('fill', component["color"]);
        rect.style['stroke'] = component["border_color"];
        rect.style['stroke-width'] = stroke_width;
        this.svg.appendChild(rect);
    }

    create2DLine({polyline, stroke_width=0.2}) {
        let poly = document.createElementNS("http://www.w3.org/2000/svg", 'polyline');
        poly.setAttribute('points', polyline);
        poly.setAttribute('fill', "none");
        poly.style['stroke'] = "0xFF0000".replace("0x", "#");
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