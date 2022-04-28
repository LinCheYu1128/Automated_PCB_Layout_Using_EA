import {readTextFile} from "./files/inputFile.js"
import {Layout} from "./Layout.js"

let placement_csv = readTextFile("./placement.csv");
let pin_csv = readTextFile("./pin.csv");
let net_csv = readTextFile("./net.csv");
let preplace_csv = readTextFile("./preplace.csv");
// let preplace_pin_csv = readTextFile("./preplace pin.csv");
let layout = new Layout(placement_csv, pin_csv, preplace_csv, net_csv);