import {CSVToArray} from "./csvParser.js"

var fileInput = document.getElementById("csvFile");
var arrData;

export function readTextFile(file) {
    var rawFile = new XMLHttpRequest();
    var data = 0;
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function() {
        if(rawFile.readyState === 4) {
            if(rawFile.status === 200 || rawFile.status == 0) {
                data = rawFile.responseText;
            }
        }
    }
    rawFile.send(null);
    arrData = CSVToArray(data);
    return arrData;
}

// function readFile() {
//     var reader = new FileReader();
//     reader.onload = function () {
//         // document.getElementById('out').innerHTML = reader.result;
//         arrData = CSVToArray(reader.result);
//         drawLayout(arrData);
//     };
//     // start reading the file. When it is done, calls the onload event defined above.
//     reader.readAsBinaryString(fileInput.files[0]);
// };

// fileInput.addEventListener('change', readFile);