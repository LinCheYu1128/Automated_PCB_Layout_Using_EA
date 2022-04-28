import * as THREE from 'https://threejsfundamentals.org/threejs/resources/threejs/r127/build/three.module.js';
import {TrackballControls} from 'https://threejsfundamentals.org/threejs/resources/threejs/r127/examples/jsm/controls/TrackballControls.js';
import {GUI} from 'https://threejsfundamentals.org/threejs/resources/threejs/r127/examples/jsm/libs/dat.gui.module.js';
import {OBJLoader} from 'https://threejsfundamentals.org/threejs/resources/threejs/r127/examples/jsm/loaders/OBJLoader.js';
import CSG from "./CSGMesh/three-csg.js";

import {readTextFile} from "./files/inputFile.js"
import {Placement_ArrayToMap} from "./Layout.js"

let camera, controls, scene, renderer, layout, lightHolder;
let mouse = new THREE.Vector2();

function init() {
    let placement_csv = readTextFile("./placement.csv");
    let placement_data = Placement_ArrayToMap(placement_csv);

    addScene({"axisHelper": false, "grid": true});
    createCamera();

    renderer = new THREE.WebGLRenderer({antialias: true, preserveDrawingBuffer: true});
    renderer.setSize(window.innerWidth-250, window.innerHeight);
    document.getElementById("3D").appendChild(renderer.domElement);
    
    let component_mesh = [];
    let component_list = {};

    createLight();
    createLayout(placement_data, {"axisHelper": false});
    createController();
}

function drawPlacement(placement_data, board_data) {
    let comp_id;
    let roots = ["F_RootHole", "B_RootHole"];
    for (let r in roots) {
        let stack = [];
        stack.push(placement_data[roots[r]]["leftChild"]);
        stack.push(placement_data[roots[r]]["rightChild"]);
        while (stack.length != 0) {
            comp_id = stack.pop();
            if (comp_id == "null") {continue;}
            createOBJGeometry(placement_data[comp_id], board_data);
            stack.push(placement_data[comp_id]["leftChild"]);
            stack.push(placement_data[comp_id]["rightChild"]);
        }
    }
}

// drawPin(name) {
//     console.log(pin_data[name]);
//     for (let [key, value] of Object.entries(pin_data[name])) {
//         create2DGeometry({"component": pin_data[name][key], "stroke_width": 0, "alignment": "center", "fill": "#111111"});
//         // createText({"component": pin_data[name][key], "name": pin_data[name][key]["name"]}); /*.slice(-1)*/
//     }
// }

function addScene(controls) {
    scene = new THREE.Scene();
    scene.background = new THREE.Color(0xffffff);

    if (controls["axisHelper"]) {
        let axesHelper = new THREE.AxesHelper(50);
        scene.add(axesHelper);
    }

    if (controls["grid"]) {
        let size = 50;
        let divisions = 50;
        let gridHelper = new THREE.GridHelper(size, divisions, 0x666666, 0xcccccc);
        scene.add(gridHelper);
    }
}

function createBoard(length, width, height) {
    let plate = {
        "size": [length, width, height],
        "position": [0, 0, 0],
        "color": "0x197531",
    };
    let hole = {
        "size": [2, 9, 1.2],
        "position": [0, 0, 0],
    };
    let box_geometry = createShapeGeometry(plate["position"], plate["size"], plate["color"]);
    let hole_geometry = createShapeGeometry(hole["position"], hole["size"], hole["color"]);
    let bspA = CSG.fromMesh(box_geometry);
    let bspB = CSG.fromMesh(hole_geometry);
    let bspResult = bspA.subtract(bspB);
    let board = CSG.toMesh(bspResult, box_geometry.matrix, box_geometry.material);
    board.translateZ(-1.2/2);
    board.name = "board";
    layout.add(board);
    return board;
}

function createLayout(placement_data, controls) {
    let length = 29.2;
    let width = 32.5;
    let height = 1.2;
    layout = new THREE.Group();

    layout.rotation.x = -Math.PI/2;
    layout.translateX(-length/2);
    layout.translateY(-width/2);    
    
    createBoard(length, width, height);
    drawPlacement(placement_data, [length, width, height]);

    scene.add(layout);

    if (controls["axisHelper"]) {
        let layoutAxis = new THREE.AxesHelper(20);
        layout.add(layoutAxis);
    }
}

function createShapeGeometry(position, size, color) {
    let shape = new THREE.Shape();
    let length = size[0], width = size[1];
    shape.moveTo(position[0], position[1]);
    shape.lineTo(position[0], position[1]+width);
    shape.lineTo(position[0]+length, position[1]+width);
    shape.lineTo(position[0]+length, position[1]);
    shape.lineTo(position[0], position[1]);
    let extrudeSettings = {
        steps: 2,
        depth: size[2],
        bevelEnabled: false,
    };
    let geometry = new THREE.ExtrudeGeometry(shape, extrudeSettings);
    let material = new THREE.MeshPhongMaterial({color: parseInt(color), side: 2});
    let mesh = new THREE.Mesh(geometry, material);
    return mesh;
}

function createOBJGeometry(component, board_data) {
    let loader = new OBJLoader();
    let comp_id = component["name"];
    let comp_color = component["color"];
    let comp_angle = component["angle"];
    let side = component["side"];
    var namelist = ["R501", "R526", "B_RootHole", "F_RootHole", "Origin"];
    if (!namelist.includes(comp_id)) {
        loader.load('./../resources/obj files/'+comp_id+'.obj',
            function (obj) {
                obj.traverse( function(child) {
                    if (child instanceof THREE.Mesh) {
                        child.name = comp_id;
                        // component_mesh.push(child);
                        setOBJPosition(child, comp_angle, side);
                        let box = new THREE.Box3().setFromObject(child);
                        box.getCenter(child.position);
                        child.position.multiplyScalar(-1);
                        child.material.color.set(comp_color);
                        child.material.transparent = true;
                    }
                });
                obj.name = comp_id;
                // component_list[comp_id] = obj;

                obj.translateX(component["margin"] + component["position"][0] + component["size"][0]/2);
                obj.translateY(component["margin"] + component["position"][1] + component["size"][1]/2);
                
                if (side == "front") {obj.translateZ(component["size"][2]/2 + board_data[2]/2);}
                else {obj.translateZ(-(component["size"][2]/2 + board_data[2]/2));}
                
                layout.add(obj);

                // let box = new THREE.BoxHelper(obj, 0xffff00);
                // box.geometry.computeBoundingBox();
                // layout.add(box);
            }
        );
    }
}

function createCamera(type="perspective") {
    if (type == "perspective") {
        camera = new THREE.PerspectiveCamera(20, window.innerWidth / window.innerHeight, 1, 1000);
    } else if (type == "orthographic") {
        let scale = 35;
        let width = (window.innerWidth-250)/scale;
        let height = window.innerHeight/scale;
        camera = new THREE.OrthographicCamera(-width, width, height, -height, 1, 500);
    }
    camera.position.set(80, 80, 80);
}

function createDirectionalLight(position, color) {
    let light = new THREE.DirectionalLight(color);
    light.position.set(...position);
    return light;
}

function createLight() {
    lightHolder = new THREE.Group();
    let light = new THREE.AmbientLight(0x808080);
    lightHolder.add(light);

    let dir_light_top = createDirectionalLight([0, 80, 0], 0xffffff);
    lightHolder.add(dir_light_top);

    let dir_light_bottom = createDirectionalLight([0, -80, 0], 0xffffff);
    lightHolder.add(dir_light_bottom);

    let dir_light_front = createDirectionalLight([80, 0, 0], 0x888888);
    lightHolder.add(dir_light_front);

    let dir_light_back = createDirectionalLight([-80, 0, 0], 0x888888);
    lightHolder.add(dir_light_back);
    
    let dir_light_left = createDirectionalLight([0, 0, 80], 0x888888);
    lightHolder.add(dir_light_left);

    let dir_light_right = createDirectionalLight([0, 0, -80], 0x888888);
    lightHolder.add(dir_light_right);

    scene.add(lightHolder);
}

function createController() {
    controls = new TrackballControls(camera, renderer.domElement);
    controls.rotateSpeed = 5;
    controls.panSpeed = 4;
    controls.zoomSpeed = 2;
    controls.dynamicDampingFactor = 1;
    controls.minDistance = 30;
    controls.maxDistance = 1000;
}

function onWindowResize() {
    console.log("resize")
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

function onMouseMove(event) {
    // calculate mouse position in normalized device coordinates
    // (-1 to +1) for both components
    // console.log(renderer.domElement.getBoundingClientRect());
    let canvasBounds = renderer.domElement.getBoundingClientRect();
    mouse.x = ((event.clientX - canvasBounds.left) / (canvasBounds.right - canvasBounds.left)) * 2 - 1;
    mouse.y = -((event.clientY - canvasBounds.top) / (canvasBounds.bottom - canvasBounds.top)) * 2 + 1;
}

function animate() {
    requestAnimationFrame(animate);
    controls.update();
    // lightHolder.quaternion.copy(camera.quaternion);
    // raytracing();
    renderer.render(scene, camera);
}

window.addEventListener('resize', onWindowResize);
window.addEventListener('mousemove', onMouseMove);

init();
animate();




let INTERSECTED;
// const raycaster = new THREE.Raycaster();

// function raytracing() {
//     camera.updateMatrixWorld();
// 	// update the picking ray with the camera and mouse position
// 	raycaster.setFromCamera( mouse, camera );
// 	// calculate objects intersecting the picking ray
// 	let intersects = raycaster.intersectObjects(component_mesh);
//     if ( intersects.length > 0 && intersects[0].object.name !== "board" ) {
//         if ( INTERSECTED != intersects[0].object ) {
//             if ( INTERSECTED ) INTERSECTED.material.emissive.setHex( INTERSECTED.currentHex );
//             INTERSECTED = intersects[0].object;
//             INTERSECTED.currentHex = INTERSECTED.material.emissive.getHex();
//             INTERSECTED.material.emissive.setHex( 0xff6060 );
//         }
//     } else {
//         if ( INTERSECTED ) INTERSECTED.material.emissive.setHex( INTERSECTED.currentHex );
//         INTERSECTED = null;
//     }
// 	// renderer.render( scene, camera );
// }


// GUI builder
// function createPanel() {
//     const panel = new GUI( { width: 400 } );

//     const folder1 = panel.addFolder( 'Visibility' );
//     const folder_camera = panel.addFolder( 'Camera' );
//     const folder2 = panel.addFolder( 'Component Information' );
//     const folder3 = panel.addFolder( 'Primary and Secondary' );
//     const folder4 = panel.addFolder( 'Routing' );

//     let settings = {
//         'show layout': true,
//         'reset board color': false,
//         'board color': 0x197531,
//         'show PrimarySecondary': false,
//         'neutral color': 0xb0b0b0,
//         'primary color': 0xd04040,
//         'secondary color': 0x4040d0,
//         'show net': false,
//         'net': {},
//         'view': "Isometry", 
//     };
//     for (let i = 0; i < Object.keys(Net).length; i++) {
//         settings['net'][Object.keys(Net)[i]] = false;
//     }
    
//     folder_camera.add(settings, 'view', { Up: "Up", Front: "Front", Bottom: "Bottom", Isometry: "Isometry" , Isometry_Back: "Isometry Back" } ).onChange(function () {
//         if (settings['view'] == "Up") {
//             controls.reset();
//             camera.up.set(0, 1, 0);
//             camera.position.set(0, 50, 0);
//         } else if (settings['view'] == "Bottom") {
//             controls.reset();
//             camera.up.set(0, 1, 0);
//             camera.position.set(0, -50, 0);
//         } else if (settings['view'] == "Front") {
//             controls.reset();
//             camera.up.set(0, 1, 0);
//             camera.position.set(50, 0, 0);
//         } else if (settings['view'] == "Isometry") {
//             controls.reset();
//             camera.up.set(0, 1, 0);
//             camera.position.set(50, 50, 50);
//         } else if (settings['view'] == "Isometry Back") {
//             controls.reset();
//             camera.up.set(0, -1, 0);
//             camera.position.set(-50, -50, 50);
//         }
//     });

//     folder1.add( settings, 'show layout' ).onChange( function() {layout.visible = settings['show layout'];} );
//     folder2.add( settings, 'reset board color' ).onChange( function() {
//         if (settings['reset board color']) {
//             board.material.color.set( parseInt(0x197531) );
//         } else {
//             board.material.color.set( settings['board color'] );
//         }
//     } );
//     folder2.addColor( settings, 'board color' ).onChange( function() {
//         if (!settings['reset board color']) {
//             board.material.color.set( settings['board color'] );
//         }
//     } );
//     folder3.add( settings, 'show PrimarySecondary' ).onChange( function() {
//         showPrimarySecondary(settings['show PrimarySecondary'], settings['neutral color'], settings['primary color'], settings['secondary color']);

//     } );
//     folder3.addColor( settings, 'neutral color' ).onChange( function() {
//         if (settings['show PrimarySecondary']) {
//             let component_name, mesh;
//             for (let attr in PrimarySecondary) {
//                 component_name = PrimarySecondary[attr];
//                 if (attr == "Neutral") {
//                     for (let i = 0; i < component_name.length; i++) {
//                         if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                             mesh = component_list[component_name[i]];
//                         } else {
//                             mesh = component_list[component_name[i]].children[0];
//                         }
//                         mesh.material.color.set( settings['neutral color'] );
//                     }
//                 }
//             }
//         }
//     } );
//     folder3.addColor( settings, 'primary color' ).onChange( function() {
//         if (settings['show PrimarySecondary']) {
//             let component_name, mesh;
//             for (let attr in PrimarySecondary) {
//                 component_name = PrimarySecondary[attr];
//                 if (attr == "Primary") {
//                     for (let i = 0; i < component_name.length; i++) {
//                         if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                             mesh = component_list[component_name[i]];
//                         } else {
//                             mesh = component_list[component_name[i]].children[0];
//                         }
//                         mesh.material.color.set( settings['primary color'] );
//                     }
//                 }
//             }
//         }
//     } );
//     folder3.addColor( settings, 'secondary color' ).onChange( function() {
//         if (settings['show PrimarySecondary']) {
//             let component_name, mesh;
//             for (let attr in PrimarySecondary) {
//                 component_name = PrimarySecondary[attr];
//                 if (attr == "Secondary") {
//                     for (let i = 0; i < component_name.length; i++) {
//                         if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                             mesh = component_list[component_name[i]];
//                         } else {
//                             mesh = component_list[component_name[i]].children[0];
//                         }
//                         mesh.material.color.set( settings['secondary color'] );
//                     }
//                 }
//             }
//         }
//     } );

//     folder4.add( settings, 'show net' ).onChange( function() {
//         let component_name, mesh;
//         for (let attr in PrimarySecondary) {
//             component_name = PrimarySecondary[attr];
//             for (let i = 0; i < component_name.length; i++) {
//                 if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                     mesh = component_list[component_name[i]];
//                 } else {
//                     mesh = component_list[component_name[i]].children[0];
//                 }
                
//                 if (settings['show net']) {
//                     let check_flag = false;
//                     mesh.material.color.set( 0xd0d0d0 );
//                     mesh.material.opacity = 0.4;
//                     for (let net = 0; net < Object.keys(Net).length; net++) {
//                         if (check_flag) {
//                             break;
//                         }
//                         if (settings['net'][Object.keys(Net)[net]]) {
//                             let list = Net[Object.keys(Net)[net]];
//                             let name_pin;
//                             for (let id in list) {
//                                 name_pin = list[id];
//                                 if (name_pin.includes(component_name[i])) {
//                                     mesh.material.color.set( 0xf04040 );
//                                     mesh.material.opacity = 1;
//                                     check_flag = true;
//                                 }
//                             }
//                         } else {
//                             mesh.material.color.set( 0xd0d0d0 );
//                             mesh.material.opacity = 0.4;
//                         }
//                     }

//                 } else {
//                     if (component_name[i] in COMP_LIST_F) {
//                         mesh.material.color.set(parseInt(COMP_LIST_F[component_name[i]]["color"]));
//                     } else {
//                         mesh.material.color.set(parseInt(COMP_LIST_B[component_name[i]]["color"]));
//                     }
//                     mesh.material.opacity = 1;
//                 }
//             }
//         }
//     } );


//     for (let net = 0; net < Object.keys(Net).length; net++) {
//         let list = Net[Object.keys(Net)[net]];
//         folder4.add( settings['net'], Object.keys(Net)[net] ).onChange( function() {
//             if (settings['show net']) {
//                 let name_pin, component_name, mesh;
//                 for (let id in list) {
//                     name_pin = list[id];
//                     for (let attr in PrimarySecondary) {
//                         component_name = PrimarySecondary[attr];
//                         for (let i = 0; i < component_name.length; i++) {
//                             if (name_pin.includes(component_name[i])) {
//                                 if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                                     mesh = component_list[component_name[i]];
//                                 } else {
//                                     mesh = component_list[component_name[i]].children[0];
//                                 }
                                
//                                 if (settings['net'][Object.keys(Net)[net]]) {
//                                     mesh.material.color.set( 0xf04040 );
//                                     mesh.material.opacity = 1;
//                                 } else {
//                                     mesh.material.color.set( 0xd0d0d0 );
//                                     mesh.material.opacity = 0.4;
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         } );
//     }

//     folder1.open();
//     folder2.open();
//     folder3.open();
//     folder4.open();
//     folder_camera.open();

// }



// function showPrimarySecondary( visibility, neutral_color, primary_color, secondary_color ) {
//     let component_name, mesh;
//     for (let attr in PrimarySecondary) {
//         component_name = PrimarySecondary[attr];
//         if (attr == "Neutral") {
//             for (let i = 0; i < component_name.length; i++) {
//                 if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                     mesh = component_list[component_name[i]];
//                 } else {
//                     mesh = component_list[component_name[i]].children[0];
//                 }
//                 if (visibility) {
//                     mesh.material.color.set(neutral_color);
//                     // mesh.material.emissive.setHex( 0x666666 );
//                 } else {
//                     if (component_name[i] in COMP_LIST_F) {
//                         mesh.material.color.set(parseInt(COMP_LIST_F[component_name[i]]["color"]));
//                     } else {
//                         mesh.material.color.set(parseInt(COMP_LIST_B[component_name[i]]["color"]));
//                     }
//                     mesh.material.emissive.setHex( 0x000000 );
//                 }
//             }
//         } else if (attr == "Primary") {
//             for (let i = 0; i < component_name.length; i++) {
//                 if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                     mesh = component_list[component_name[i]];
//                 } else {
//                     mesh = component_list[component_name[i]].children[0];
//                 }
//                 if (visibility) {
//                     mesh.material.color.set(primary_color);
//                     // mesh.material.emissive.setHex( 0x666666 );
//                 } else {
//                     if (component_name[i] in COMP_LIST_F) {
//                         mesh.material.color.set(parseInt(COMP_LIST_F[component_name[i]]["color"]));
//                     } else {
//                         mesh.material.color.set(parseInt(COMP_LIST_B[component_name[i]]["color"]));
//                     }
//                     mesh.material.emissive.setHex( 0x000000 );
//                 }
//             }
//         } else if (attr == "Secondary") {
//             for (let i = 0; i < component_name.length; i++) {
//                 if (component_list[component_name[i]] instanceof THREE.Mesh) {
//                     mesh = component_list[component_name[i]];
//                 } else {
//                     mesh = component_list[component_name[i]].children[0];
//                 }
//                 if (visibility) {
//                     mesh.material.color.set(secondary_color);
//                     // mesh.material.emissive.setHex( 0x666666 );
//                 } else {
//                     if (component_name[i] in COMP_LIST_F) {
//                         mesh.material.color.set(parseInt(COMP_LIST_F[component_name[i]]["color"]));
//                     } else {
//                         mesh.material.color.set(parseInt(COMP_LIST_B[component_name[i]]["color"]));
//                     }
//                     mesh.material.emissive.setHex( 0x000000 );
//                 }
//             }
//         }
//     }
// }

// createPanel();
// console.log(component_list)

function setOBJPosition(geometry, angle, side) {
    let deg_90 = Math.PI/2;
    
    // geometry.rotateX(deg_90);
    // geometry.rotateY(deg_90);

    // rotate angle
    geometry.rotateY(deg_90*(angle/90));
    
    // flip
    if (side == "back"){
        geometry.rotateX(Math.PI);
    }

    if (geometry.name == "T501") {
        geometry.rotateY(Math.PI);
    }
}