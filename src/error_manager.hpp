#pragma once


struct ErrorManager
{
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


};
