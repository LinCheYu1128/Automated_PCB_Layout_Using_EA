import {Canvas} from "./svg canvas.js";
import {drawTree} from "./drawTree.js";

export function drawLayout(arrData) {
    let mapData = ArrayToMap(arrData);
    console.log(mapData)
    // let layout = new Canvas("single", mapData);
    let front_layout = new Canvas("front", mapData);
    let back_layout = new Canvas("back", mapData);
    drawTree({divID: 'Tree', width: 1500, height: 800, padding: 50, treeData: MapToTree(mapData, arrData)});
}

function ArrayToMap(arrData) {
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
            "side": component[8],
            "angle": Number(component[9]),
            "leftChild": component[10],
            "rightChild": component[11],
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