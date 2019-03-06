#ifndef DEVICESTRUCT_H
#define DEVICESTRUCT_H

#include  "QtCore"

struct device
{
    uint        id;
    QString     order_number;
    QString     manufacterer;
    QString     vendor;
    QString     part_number;
    uint        power;
    uint        working_voltage;
    float       current;
    double      estimated_price;
    double      frequency;
    float       width;
    float       height;
    uint        noOfDigOutput;
    uint        noOfDigInput;
    uint        noOfAnOutput;
    uint        noOfAnInput;
    QString     PLC_tags[10];
    uint        assemble_time;
};

struct connection
{
    uint        id;
    QString     order_number;
    QString     manufacterer;
    float       cable_dia;
    QString     vendor;
    QString     part_number;
    uint        power;
    uint        working_voltage;
    float       current;
    double      estimated_price;
    QString     color;
    QString     terminal_group;
};

struct cable
{
    uint        id;
    QString     order_number;
    QString     manufacterer;
    QString     vendor;
    QString     part_number;
    uint        power;
    uint        working_voltage;
    float       current;
    double      estimated_price;
    double      core_diameter;
    uint        noOfCore;
    int         working_temperature;
    bool        flexible;
    bool        isolated;
    QString     cable_group;
    int         production_time;
};

struct ventilation_unit
{
    device              motor[10];
    device              motorProtector[10];
    device              motorContactor[10];
    device              motorAuxContact[20];
    connection          motorTerminal[50];
    connection          motorPhaseMultiplier;
    cable               motorCable[300];
    double              totalUnitPower;
    double              totalUnitCurrent;

};





#endif // DEVICESTRUCT_H
