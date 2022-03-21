import {Canvas} from "./svg canvas.js";
import {drawTree} from "./drawTree.js"

export class Layout {
    constructor(placement_csv, pin_csv, net_csv) {
        let placement_mapData = Placement_ArrayToMap(placement_csv);
        let pin_mapData = Pin_ArrayToMap(pin_csv);
        let net_mapData = Net_ArrayToMap(net_csv);
        let layout_front = new Canvas("front", {"placement_data": placement_mapData, "pin_data": pin_mapData, "net_data": net_mapData});
        let layout_back = new Canvas("back", {"placement_data": placement_mapData, "pin_data": pin_mapData, "net_data": net_mapData});

        drawTree({divID: 'Tree', width: 1500, height: 800, padding: 50, treeData: MapToTree(placement_mapData, placement_csv)});
    }
};

function Placement_ArrayToMap(arrData) {
    let mapData = {};
    let component;
    for (let i = 0; i < arrData.length; i++) {
        component = arrData[i];
        mapData[component[0]] = {
            "name": component[0],
            "color": "#"+component[1],
            "size": [Number(component[2]), Number(component[3]), Number(component[4])],
            "voltage": Number(component[5]),
            "position": [Number(component[6]), Number(component[7])],
            "margin": Number(component[8]),
            "side": component[9],
            "angle": Number(component[10]),
            "leftChild": component[11],
            "rightChild": component[12],
        }
    }
    return mapData;
}

function Pin_ArrayToMap(arrData) {
    let mapData = {};
    let pin_id;
    for (let i = 0; i < arrData.length; i++) {
        pin_id = arrData[i];
        mapData[pin_id[0]] = {
            "name": pin_id[0],
            "size": [Number(pin_id[1]), Number(pin_id[2])],
            "position": [Number(pin_id[3]), Number(pin_id[4])],
        }
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