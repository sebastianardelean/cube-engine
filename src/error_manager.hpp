#pragma once


struct ErrorManager
{
    void RegisterCallback(std::function<void(int16_t)> callback)
    {
	fCallback = callback;
    }
    void StoreError(int16_t error)
    {
	nError=error;
    }
    [[nodiscard]] int16_t GetError(int16_t error) 
    {
	return nError;
    }
    private:
	int16_t nError;

    private:
	std::function<void(int16_t)> fCallback;
};
