import {CSVToArray} from "./csvParser.js"
import {drawLayout} from "../drawLayout.js"

var fileInput = document.getElementById("csvFile");
var arrData;

function readFile() {
    var reader = new FileReader();
    reader.onload = function () {
        // document.getElementById('out').innerHTML = reader.result;
        arrData = CSVToArray(reader.result);
        drawLayout(arrData);
    };
    // start reading the file. When it is done, calls the onload event defined above.
    reader.readAsBinaryString(fileInput.files[0]);
};

fileInput.addEventListener('change', readFile);