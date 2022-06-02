import {Component} from "./geometry.js";
import {SVG_Controller} from "./svg controller.js";



export class Canvas {
    constructor(side, data) {
        this.placement_data = data["placement_data"];
        this.preplace_data = data["preplace_data"];
        this.pin_data = data["pin_data"];
        this.net_data = data["net_data"];
        this.route_dict = data["route_data"];
        this.color_dict = data["color"];
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
        console.log(this.color_dict);
        this.drawGrid();
        this.drawBoundary();
        
        this.drawPlacement();
        this.drawRoute();
        // this.drawPreplace();
        document.getElementById('Layout_'+this.side).appendChild(this.svg);
    }

    drawRoute() {
        let net_color;
        // var a = 13.01 + 5.5;
        // console.log("test",a);
        // iterate Net
        for (let i = 0; i < Object.keys(this.route_dict).length; i++) {
            net_color = this.color_dict[i];
            // iterate route of each Net
            // console.log(this.route_dict[Object.keys(this.route_dict)[i]]);
            for (const [key, value] of Object.entries(this.route_dict[Object.keys(this.route_dict)[i]])) {
                // console.log("raw",value[0]);
                let x1 = Number(value[0]) + 5.5;
                // console.log(x1);
                let y1 = Number(value[1]) + 5.5;
                let x2 = Number(value[2]) + 5.5;
                let y2 = Number(value[3]) + 5.5;
                this.create2DRoute({"polyline":`${x1}, ${y1} ${x2}, ${y2}`, stroke: net_color, stroke_width: 0.1});
            }
        }
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
            // placement_data[comp_id]["side"] = this.side;
            this.create2DGeometry({"component": placement_data[comp_id]});
            this.createText({"component": placement_data[comp_id]});
            // console.log(comp_id);
            this.drawPin(comp_id);
            stack.push(placement_data[comp_id]["leftChild"]);
            stack.push(placement_data[comp_id]["rightChild"]);
        }
    }

    drawPreplace() {
        let preplace_data = this.preplace_data;
        let stack = [];

        for (let [comp_id, value] of Object.entries(this.preplace_data)) {
            if (preplace_data[comp_id]["side"] == this.side) {
                this.create2DGeometry({"component": preplace_data[comp_id]});
                this.createText({"component": preplace_data[comp_id]});
                this.drawPin(comp_id);
            }

            if (preplace_data[comp_id]["side"] != this.side && preplace_data[comp_id]["pierce"] == "1") {
                this.drawPin(comp_id, true);
            }
        }
    }

    drawPin(name, pierce=false) {
        // console.log(this.pin_data[name]);
        for (let [key, value] of Object.entries(this.pin_data[name])) {
            if (pierce) {
                this.pin_data[name][key]["color"] = "#FF0000";
            } else {
                this.pin_data[name][key]["color"] = "#000000";
            }
            this.create2DGeometry({"component": this.pin_data[name][key], "stroke_width": 0, "alignment": "center"});
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

    create2DGeometry({component, alignment="bottom_left"}) {
        let rect = document.createElementNS("http://www.w3.org/2000/svg", 'rect');
        let rect_margin = document.createElementNS("http://www.w3.org/2000/svg", 'rect');

        if (alignment == "bottom_left") {
            console.log(component["name"], component["size"][0], component["size"][1])
            rect.setAttribute('x', this.margin_x + component["margin"] + component["position"][0]);
            rect.setAttribute('y', this.margin_y + component["margin"] + component["position"][1]);
            rect.setAttribute('width', component["size"][0]);
            rect.setAttribute('height', component["size"][1]);

            rect_margin.setAttribute('x', this.margin_x + component["position"][0]);
            rect_margin.setAttribute('y', this.margin_y + component["position"][1]);
            rect_margin.setAttribute('width', component["size"][0] + 2*component["margin"]);
            rect_margin.setAttribute('height', component["size"][1] + 2*component["margin"]);
        } else if (alignment == "center") {
            rect.setAttribute('x', this.margin_x + component["margin"] + (component["position"][0] - component["size"][0]/2));
            rect.setAttribute('y', this.margin_y + component["margin"] + (component["position"][1] - component["size"][1]/2));
            rect.setAttribute('width', component["size"][0]);
            rect.setAttribute('height', component["size"][1]);

            rect_margin.setAttribute('x', this.margin_x + (component["position"][0] - component["size"][0]/2));
            rect_margin.setAttribute('y', this.margin_y + (component["position"][1] - component["size"][1]/2));
            rect_margin.setAttribute('width', component["size"][0] + 2*component["margin"]);
            rect_margin.setAttribute('height', component["size"][1] + 2*component["margin"]);
        }
        
        rect.setAttribute('name', component["name"]);
        rect.setAttribute('original-fill', component["color"]);
        rect.setAttribute('fill', component["color"]);

        if (component["voltage"] == "1") {
            rect.setAttribute('PNS-fill', '#FF000066');
            rect_margin.style['fill'] = '#FF000088';
        } else if (component["voltage"] == "-1") {
            rect.setAttribute('PNS-fill', '#0000FF66');
            rect_margin.style['fill'] = '#0000FF88';
        } else {
            rect.setAttribute('PNS-fill', '#11111166');
            rect_margin.style['fill'] = '#00000088';
        }
        rect_margin.style['stroke'] = '#666666';
        rect_margin.style['stroke-width'] = 0.01;
        rect_margin.style.display = "none";

        rect.classList.add("component");
        rect_margin.classList.add("component-margin");

        this.svg.appendChild(rect);
        this.svg.appendChild(rect_margin);
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

    create2DRoute({polyline, stroke="#666666", stroke_width=0.2}) {
        let poly = document.createElementNS("http://www.w3.org/2000/svg", 'polyline');
        poly.setAttribute('points', polyline);
        poly.setAttribute('fill', "none");
        poly.style['stroke'] = stroke;
        poly.style['stroke-width'] = stroke_width;
        poly.classList.add("route");
        this.svg.appendChild(poly);
        return;
    }

    createText({component}) {
        let text = document.createElementNS("http://www.w3.org/2000/svg", 'text');
        text.setAttribute('x', this.margin_x + (component["position"][0] + component["margin"] + component["size"][0]/2));
        text.setAttribute('y', this.margin_y + (component["position"][1] + component["margin"] + component["size"][1]/2));
        text.style['font'] = "0.5px \"Lato\", sans-serif";
        text.style['dominant-baseline'] = "middle";
        text.style['text-anchor'] = "middle";
        text.textContent = component.name;
        let x = this.margin_x + (component["position"][0] + component["margin"] + component["size"][0]/2);
        let y = this.margin_y + (component["position"][1] + component["margin"] + component["size"][1]/2);
        if (this.side == "front" || this.side == "single") {
            text.setAttribute('transform', `translate(${x}, ${y}) scale(1, -1) translate(${-x}, ${-y})`);
        } else {
            text.setAttribute('transform', `translate(${x}, ${y}) rotate(180) translate(${-x}, ${-y})`);
        }
        this.svg.appendChild(text);
    }
}