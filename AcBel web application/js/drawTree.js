export function drawTree(o) {
    let radius = 20;
    d3.select("#"+o.divID).select("svg").remove();
    var viz = d3.select("#"+o.divID).append("svg").attr("width", o.width).attr("height", o.height);
    var vis = viz.append("g").attr("id","treeg").attr("transform", "translate("+ o.padding +","+ o.padding +")");
    var tree = d3.layout.tree().size([o.width - (2 * o.padding), o.height - (2 * o.padding)]);
    var diagonal = d3.svg.diagonal().projection(function(d) { return [d.x, d.y]; });
    var nodes = tree.nodes(o.treeData);
    var link = vis.selectAll("pathlink").data(tree.links(nodes)).enter().append("path").attr("class", "link").attr("d", diagonal);
    var node = vis.selectAll("g.node").data(nodes).enter().append("g").attr("transform", function(d) { return "translate(" + d.x + "," + d.y + ")"; });
    node.append("circle").attr("r", radius).style("fill", function(d) { return (d.children) ? "#E14B3B" : "#1C8B98" });
    node.append("svg:text").attr("dx", function(d) { return d.children ? 0 : 0; }).attr("dy", function(d) { return d.children ? 5 : 5; })
        .attr("text-anchor", function(d) { return d.children ? "middle" : "middle"; }).style("fill", "white").text(function(d) { return d.name; });
}

let treeData = {
    "name": "F_RootHole",
    "size": [2, 9, 0.1],
    "position": [2.125, 2.125, 0],
    "angle": "0",
    "color": "0x0",
    children: [
        {
            "name": "M503",
            "size": [13.5, 9.4, 1.35],
            "position": [4.375, 2.125, 0],
            "angle": "1",
            "color": "0x1a1a1a",
            children: [
                {
                    "name": "C512",
                    "size": [1.9, 3.5, 1.9],
                    "position": [18.125, 2.125, 0],
                    "angle": "1",
                    "color": "0xf27a46",
                },
                // {
                //     "name": "R526",
                //     "size": [0.8, 1.6, 0.45],
                //     "position": [20.275, 2.125, 0],
                //     "angle": "0",
                //     "color": "0x0361ad",
                // },
            ]
        },
        {
            "name": "R515",
            "size": [1.6, 3.2, 0.6],
            "position": [21.325, 2.125, 0],
            "angle": "1",
            "color": "0x6857b5",
        }
    ]
}
// drawTree({divID: 'Tree', width: 1000, height: 800, padding: 50, treeData: treeData});
// drawTree({divID: 'viz', width: 1000, height: 800, padding: 50, treeData: {name: 'S', children: [{name: 'S', children: [{name: 'S', children: [{name: 'S', children: [{name: 'x'}]}, {name: 'S', children: [{name: 'y'}]}, {name: '*'}]}, {name: 'S', children: [{name: '1'}]}, {name: '+'}]}, {name: 'S', children: [{name: 'S', children: [{name: '1'}]}, {name: '-'}]}, {name: '+'}]}})