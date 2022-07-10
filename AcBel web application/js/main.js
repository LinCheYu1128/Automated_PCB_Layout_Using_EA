import {readTextFile} from "./files/inputFile.js"
import {Layout} from "./Layout.js"

function myrefresh(){
    window.location.reload();
}

function exportSVG(id, filename) {
    console.log(document.getElementById(id).children[0])
    var svgData = document.getElementById(id).children[0];
    var serializer = new XMLSerializer();
    var source = serializer.serializeToString(svgData);
    var svgUrl = "data:image/svg+xml;charset=utf-8,"+encodeURIComponent(source);
    var downloadLink = document.createElement("a");
    downloadLink.download = filename;
    downloadLink.href = svgUrl;

    document.body.appendChild(downloadLink);
    downloadLink.click();
    document.body.removeChild(downloadLink);
}

for(let i=0; i<1; i++){
    window.setTimeout(()=>{
        let placement_csv = readTextFile("./animation/result/placement_" + i + ".csv");
        // let pin_csv = readTextFile("./pin.csv");
        let pin_csv = readTextFile("./animation/result/pin_" + i + ".csv");
        let net_csv = readTextFile("./net.csv");
        let preplace_csv = readTextFile("./preplace.csv");
        let route_csv = readTextFile("./route.csv");
        let layout = new Layout(placement_csv, pin_csv, preplace_csv, net_csv, route_csv);

        // exportSVG('Layout_back', 'generation_back_'+ i + '.svg');
        
        document.getElementById("Layout_front").innerHTML = "";
        document.getElementById("Layout_back").innerHTML = "";

        // const context = canvas.getContext('2d');
        // context.clearRect(0, 0, canvas.width, canvas.height);

    }, (i+1) * 500);
}



