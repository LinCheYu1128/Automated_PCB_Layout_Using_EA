import {readTextFile} from "./files/inputFile.js"
import {Layout} from "./Layout.js"

let placement_csv = readTextFile("./placement.csv");
let pin_csv = readTextFile("./pin.csv");
let net_csv = readTextFile("./net.csv");
let layout = new Layout(placement_csv, pin_csv, net_csv);