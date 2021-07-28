#pragma once

enum ErrorCode:int16_t
{
    Event_NoError = 0,
}

struct ErrorEvent {
    ErrorEvent() {
	eventType = Event_NoError;
	msg = "";
    }

    ErrorEvent(const ErrorCode event,const std::string errorMessage):eventType(event),msg(errorMessage) {
    }

    [[nodiscard]]ErrorCode GetEventType() const {
	return eventType;
    }

    [[nodiscard]] std::string GetErrorMessage() const {
	return msg;
    }

    protected:
	ErrorCode eventType;
	std::string msg;
}

struct FatalErrorEvent:public ErrorEvent
{
    FatalErrorEvent(ErrorCode code):ErrorEvent(code,"")
    {
    }
}
