export class Component {
    constructor({size={x: 0, y: 0}, position={x: 0, y: 0}, color="#FFFFFF", border_color="#000000"}) {
        this.size = {"x": size.x, "y": size.y};
        this.position = {"x": position.x, "y": position.y};
        this.color = color;
        this.border_color = border_color;
    }
}