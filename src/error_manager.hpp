#pragma once

enum ErrorCode:int16_t
{
    Event_NoError = 0,
    Event_FatalError = 1,
    Event_SdlError = 2
};

struct ErrorEvent {
    ErrorEvent() {
	errorCode = Event_NoError;
	msg = "";
    }

    ErrorEvent(const ErrorCode error,const std::string errorMessage):errorCode(error),msg(errorMessage) {
    }

    [[nodiscard]]ErrorCode GetErrorCode() const {
	return errorCode;
    }

    [[nodiscard]] std::string GetErrorMessage() const {
	return msg;
    }

    protected:
	ErrorCode errorCode;
	std::string msg;
};

struct FatalErrorEvent:public ErrorEvent
{
    FatalErrorEvent():ErrorEvent(Event_FatalError,"")
    {
    }
};

class ErrorManager
{
    public:
	static std::shared_ptr<ErrorManager> &GetInstance() {
	    static std::shared_ptr<ErrorManager> instance = nullptr;
		if (!instance) {
		    std::lock_guard lock(ErrorManager::_mutex);

		if (!instance) {
		    instance.reset(new ErrorManager());
		}
	    }
	    return instance;
	}
	~ErrorManager() {}
	void RegisterCallback(std::function<void(ErrorEvent)> callback)
	{
	    fCallback = callback;
	}
	void StoreError(ErrorEvent e)
	{
	    errors.push_back(e);
	    fCallback(e);
	
	}
	[[nodiscard]] ErrorEvent GetLastError() 
	{
	    if (!errors.empty()) {
		return errors.back();
	    }   
	    return ErrorEvent(Event_NoError,"No errors stored");
	}
    private:
        ErrorManager() {}
	ErrorManager(const ErrorManager&) = delete;
	ErrorManager(ErrorManager &&) = delete;
	ErrorManager &operator = (const ErrorManager&) = delete;
	ErrorManager &operator = (ErrorManager &&) = delete;
	std::vector<ErrorEvent> errors;
	std::function<void(ErrorEvent)> fCallback;
	static std::mutex _mutex;
};
