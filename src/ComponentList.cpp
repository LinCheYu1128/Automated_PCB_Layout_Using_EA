#include "../includes/ComponentList.h"

ComponentList::ComponentList(Component_Path comp_info) {
    this->comp_info = comp_info;
    setAllData();
}

ComponentList::~ComponentList() {
    auto iter = comp_data.begin();
    while (iter != comp_data.end()) {
        delete iter->second;
        ++iter;
    }
}

ComponentProperty* ComponentList::getData(string comp_name) {
    return comp_data[comp_name];
}

map<string, ComponentProperty*> ComponentList::getAllData() {
    return comp_data;
}

void ComponentList::setData(string comp_name, ComponentProperty* comp_prop) {
    comp_data[comp_name] = comp_prop;
}

void ComponentList::setPinPosition(string comp_name) {
    ifstream inFile(comp_info.pinPosition_relativePath + comp_name + ".csv");
    string key;
    string temp;
    Point point;
    if (!inFile) {
        // cout << "can't open file" << endl;
        return;
    } else {
        // cout << "can open " << comp_name << " file" << endl;
    }

    while (!inFile.eof()) {
        getline(inFile, temp, ',' );
        key = temp;
        getline(inFile, temp, ',' );
        point.x = stod(temp);
        getline(inFile, temp, '\n' );
        point.y = stod(temp);
        comp_data[comp_name]->setOneDefaultPinPosition(key, point);
    }
}

void ComponentList::setAllData() {
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

void ComponentList::printData(string comp_name) {
    cout << "[ component " << comp_data[comp_name] << " | "
         << "name: " << comp_data[comp_name]->getName()
         << ", length:" << comp_data[comp_name]->getLength()
         << ", width:" << comp_data[comp_name]->getWidth()
         << ", height:" << comp_data[comp_name]->getHeight()
         << ", voltage:" << comp_data[comp_name]->getVoltage()
         << " ]" << endl;
         comp_data[comp_name]->printDefaultPinPosition();
}

void ComponentList::printAllData() {
    auto iter = comp_data.begin();
    while (iter != comp_data.end()) {
        cout << "[ component " << iter->first << " | "
             << "name: " << iter->second->getName()
             << ", length:" << iter->second->getLength()
             << ", width:" << iter->second->getWidth()
             << ", height:" << iter->second->getHeight()
             << ", voltage:" << iter->second->getVoltage()
             << " ]" << endl;
        iter->second->printDefaultPinPosition();
        ++iter;
    }
}