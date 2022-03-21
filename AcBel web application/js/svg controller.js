export class SVG_Controller {
    constructor(width, height, margin_x, margin_y) {
        this.svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
        this.moving = false;
        this.svg.setAttribute("width", "100%");
        this.svg.setAttribute("height", "100%");
        this.svg.setAttribute("viewBox", `-${0} -${0} ${width+2*margin_x} ${height+2*margin_y}`);
        // this.svg.setAttribute("viewBox", `-${0} ${height+2*margin_y} ${width+2*margin_x} ${0}`);
        //	拖曳的事件
        this.svg.addEventListener('mousedown', e=>{this.mouseDown(e)}, false);
        this.svg.addEventListener('mousemove', e=>{this.drag(e)}, false);
        this.svg.addEventListener('mouseup', e=>{this.mouseUp(e)}, false);
        //	縮放的事件
        this.svg.addEventListener('wheel', e=>{this.zoom(e)}, false);
    }

    mouseDown(e) {
        console.log("mouse Down");
        this.moving = true;
        // console.log("mouse Down", this.moving);
    }

    drag(e) {
        console.log("mouse Drag", this.moving);
        // console.log("111", this.svg)({"svg": this.svg})
        if (this.moving === true) {
            //	1. 取得一開始的 viewBox 值，原本是字串，拆成陣列，方便之後運算
            console.log(this.svg.getAttribute('viewBox'))
            let startViewBox = this.svg.getAttribute('viewBox').split(' ').map( n => parseFloat(n));

            //	2. 取得滑鼠當前 viewport 中 client 座標值
            let startClient = {
                "x": e.clientX,
                "y": e.clientY
            };

            //	3. 計算對應回去的 SVG 座標值
            let newSVGPoint = this.svg.createSVGPoint();
            let CTM = this.svg.getScreenCTM();
            newSVGPoint.x = startClient.x;
            newSVGPoint.y = startClient.y;
            let startSVGPoint = newSVGPoint.matrixTransform(CTM.inverse());
            
            //	4. 計算拖曳後滑鼠所在的 viewport client 座標值
            let moveToClient = {
                "x": e.clientX + e.movementX,	//	movement 可以取得滑鼠位移量
                "y": e.clientY + e.movementY
            };
            
            //	5. 計算對應回去的 SVG 座標值
            newSVGPoint = this.svg.createSVGPoint()
            CTM = this.svg.getScreenCTM()
            newSVGPoint.x = moveToClient.x;
            newSVGPoint.y = moveToClient.y;
            let moveToSVGPoint = newSVGPoint.matrixTransform(CTM.inverse())
            
            //	6. 計算位移量
            let delta = {
                "dx": startSVGPoint.x - moveToSVGPoint.x,
                "dy": startSVGPoint.y - moveToSVGPoint.y
            };
            
            //	7. 設定新的 viewBox 值
            let moveToViewBox = `${startViewBox[0] + delta.dx} ${startViewBox[1] + delta.dy} ${startViewBox[2]} ${startViewBox[3]}`;
            this.svg.setAttribute('viewBox', moveToViewBox);
            console.log(moveToViewBox);
        }
    }
    //	滑鼠點擊結束（拖曳結束）
    mouseUp() {
        console.log("mouse Up");
        this.moving = false;
    }
    //	結束：滑鼠拖拉的效果

        
    /*	
    開始：滑鼠縮放的效果
    */
    zoom(e) {
        //	1.取得一開始的 viewBox。
        let startViewBox = this.svg.getAttribute('viewBox').split(' ').map( n => parseFloat(n));
            
        //	2.取得滑鼠執行縮放位置的 viewPort Client 座標，並利用 CTM 對應取得 SVG 座標。

        //	2.1 取得滑鼠執行縮放的位置
        let startClient = {
            "x": e.clientX,
            "y": e.clientY
        }

        //	2.2 轉換成 SVG 座標系統中的 SVG 座標點
        let newSVGPoint = this.svg.createSVGPoint();
        let CTM = this.svg.getScreenCTM()
        newSVGPoint.x = startClient.x;
        newSVGPoint.y = startClient.y;
        let startSVGPoint = newSVGPoint.matrixTransform(CTM.inverse());


        //	3.進行縮放，如果要讓原本的尺寸縮放兩倍的話。
        //	3.1 設定縮放倍率
        let r;
        if (e.deltaY > 0) {
            r = 0.9;
        } else if (e.deltaY < 0) {
            r = 1.1;
        } else {
            r = 1;
        }
        //	3.2 進行縮放
        this.svg.setAttribute('viewBox', `${startViewBox[0]} ${startViewBox[1]} ${startViewBox[2] * r} ${startViewBox[3] * r}`);

        //	4.將一開始滑鼠的執行縮放位置的 viewPort Client 座標利用新的 CTM ，轉換出對應的 SVG 座標。
        CTM = this.svg.getScreenCTM();
        let moveToSVGPoint = newSVGPoint.matrixTransform(CTM.inverse());

        //	5.取得在縮放過程中該圓點的位移量 `(svgX0 - svgX1)`。
        let delta = {
            "dx": startSVGPoint.x - moveToSVGPoint.x,
            "dy": startSVGPoint.y - moveToSVGPoint.y
        };

        //	6.設定最終的 viewBox2 
        let middleViewBox = this.svg.getAttribute('viewBox').split(' ').map( n => parseFloat(n));
        let moveBackViewBox = `${middleViewBox[0] + delta.dx} ${middleViewBox[1] + delta.dy} ${middleViewBox[2]} ${middleViewBox[3]}`;
        this.svg.setAttribute('viewBox', moveBackViewBox);
    }	//	結束：滑鼠縮放的效果
}