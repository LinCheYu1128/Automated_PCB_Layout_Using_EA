import {Canvas} from "./svg canvas.js";
import {drawTree} from "./drawTree.js"

export class Layout {
    constructor(placement_csv, pin_csv, net_csv) {
        this.component_data = {};
        let placement_mapData = Placement_ArrayToMap(placement_csv);
        let pin_mapData = Pin_ArrayToMap(pin_csv);
        let net_mapData = Net_ArrayToMap(net_csv);
        let layout_front = new Canvas("front", {"placement_data": placement_mapData, "pin_data": pin_mapData, "net_data": net_mapData});
        let layout_back = new Canvas("back", {"placement_data": placement_mapData, "pin_data": pin_mapData, "net_data": net_mapData});

        drawTree({divID: 'Tree', width: 1500, height: 800, padding: 50, treeData: MapToTree(placement_mapData, placement_csv)});
    }

    importPlacement(arrData) {
        let component;
        for (let i = 0; i < arrData.length; i++) {
            component = arrData[i];
            this.component_data[component[0]] = {
                "name": component[0],
                "color": "#"+component[1],
                "size": [Number(component[2]), Number(component[3]), Number(component[4])],
                "voltage": Number(component[5]),
                "position": [Number(component[6]), Number(component[7])],
                "margin": Number(component[8]),
                "angle": Number(component[9]),
                "side": component[10],
                "leftChild": component[11],
                "rightChild": component[12],
                "pin_position": {},
            }
        }
    }

    importPin(arrData) {
        let pin, name;
        for (let i = 0; i < arrData.length; i++) {
            pin = arrData[i];
            name = pin[0];
            if (!this.component_data[name]) {this.component_data[name] = {};}
            this.component_data[name][pin[1]] = {
                "name": pin[1],
                "size": [Number(pin[2]), Number(pin[3])],
                "position": [Number(pin[4]), Number(pin[5])],
            };
        }
    }
};

function Placement_ArrayToMap(arrData) {
    let mapData = {};
    let component;
    let  shift = 0.5;
    for (let i = 0; i < arrData.length; i++) {
        component = arrData[i];
        mapData[component[0]] = {
            "name": component[0],
            "color": "#"+component[1],
            "size": [Number(component[2]), Number(component[3]), Number(component[4])],
            "voltage": Number(component[5]),
            "position": [Number(component[6]) + shift, Number(component[7]) + shift],
            "margin": Number(component[8]),
            "angle": Number(component[9]),
            "side": component[10],
            "leftChild": component[11],
            "rightChild": component[12],
        }
    }
    return mapData;
}

function Pin_ArrayToMap(arrData) {
    let mapData = {};
    let pin;
    let  shift = 0.5;
    for (let i = 0; i < arrData.length; i++) {
        pin = arrData[i];
        if (!mapData[pin[0]]) {mapData[pin[0]] = {};}
        mapData[pin[0]][pin[1]] = {
            "name": pin[0] + "-" + pin[1],
            "size": [Number(pin[2]), Number(pin[3])],
            "position": [Number(pin[4]) + shift, Number(pin[5]) + shift],
            "margin": 0,
        };
    }
    return mapData;
}

function Net_ArrayToMap(arrData) {
    let mapData = {};
    let pin_id;
    for (let i = 0; i < arrData.length; i++) {
        pin_id = arrData[i];
        mapData[pin_id[0]] = {
            "name": pin_id[0],
            "begin": pin_id[1],
            "end": pin_id[2],
        }
    }
    return mapData;
}

function MapToTree(mapData, arrData) {
    let Tree = {};
    let queue = [];
    let temp, node, component;

    component = mapData[arrData[0][0]];
    Tree["name"] = component["name"];
    Tree["children"] = [{"name": component["leftChild"]}, {"name": component["rightChild"]}];
    queue.push({"node": Tree["children"][0], "component": mapData[component["leftChild"]]}, {"node": Tree["children"][1], "component": mapData[component["rightChild"]]});
    
    while (queue.length != 0) {
        temp = queue.pop();
        node = temp["node"];
        if (node["name"] == "null") {
            continue;
        }
        component = temp["component"];
        node["children"] = [];
        node["children"] = [{"name": component["leftChild"]}, {"name": component["rightChild"]}];
        queue.push({"node": node["children"][0], "component": mapData[component["leftChild"]]}, {"node": node["children"][1], "component": mapData[component["rightChild"]]});
    }

    console.log(Tree)
    return Tree;
}