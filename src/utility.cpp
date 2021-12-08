#include "../includes/utility.h"

ComponentList_Reader::ComponentList_Reader(Component_Info comp_info) {
    this->comp_info = comp_info;
    setAllData();
}

map<string, ComponentProperty*> ComponentList_Reader::getData() {
    return comp_data;
}

void ComponentList_Reader::setData(string comp_name, ComponentProperty* comp_prop) {
    comp_data[comp_name] = comp_prop;
}

void ComponentList_Reader::setPinPosition(string comp_name) {
    ifstream inFile(comp_info.pinPosition_relativePath + comp_name + ".csv");
    string key;
    string temp;
    Point point;
    if (!inFile) {
        cout << "can't open file" << endl;
        return;
    } else {
        cout << "can open " << comp_name << " file" << endl;
    }

    while (!inFile.eof()) {
        getline(inFile, temp, ',' );
        key = temp;
        getline(inFile, temp, ',' );
        point.x = stod(temp);
        getline(inFile, temp, '\n' );
        point.y = stod(temp);
        comp_data[comp_name]->setPinPosition(key, point);
    }
}

void ComponentList_Reader::setAllData() {
    ifstream inFile(comp_info.component_relativePath + comp_info.component_csvfile);
    string temp;

    getline(inFile, temp, '\n');
    while (!inFile.eof()) {
        ComponentProperty* comp_prop = new ComponentProperty();
        getline(inFile, temp, ',' );
        comp_prop->setName(temp);
        getline(inFile, temp, ',' );
        comp_prop->setColor(temp);
        getline(inFile, temp, ',' );
        comp_prop->setLength(stod(temp));
        getline(inFile, temp, ',' );
        comp_prop->setWidth(stod(temp));
        getline(inFile, temp, ',' );
        comp_prop->setHeight(stod(temp));
        getline(inFile, temp, '\n' );
        comp_prop->setVoltage(stod(temp));

        setData(comp_prop->getName(), comp_prop);
        setPinPosition(comp_prop->getName());
    }
}

void ComponentList_Reader::printData() {
    map<string, ComponentProperty*> data = getData();
    auto iter = data.begin();
    while (iter != data.end()) {
        cout << "[ component " << iter->first << " | "
             << "name: " << iter->second->getName()
             << ", length:" << iter->second->getLength()
             << ", width:" << iter->second->getWidth()
             << ", height:" << iter->second->getHeight()
             << ", voltage:" << iter->second->getVoltage()
             << " ]" << endl;
        iter->second->printPinPosition();
        ++iter;
    }
}