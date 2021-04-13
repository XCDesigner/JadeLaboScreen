#include "Event.h"

JLEvent event_unit;

QList<strEventTCB> JLEvent::event_list;


JLEvent::JLEvent(QObject *parent) : QObject(parent)
{

}

bool JLEvent::SetListen(uint8_t Command, uint8_t SubCode, void* pFunction)
{
    strEventTCB new_event;
    new_event.Command = Command;
    new_event.SubCode = SubCode;
    new_event.pCallback = &pFunction;
    event_list.append(new_event);
}
