#pragma once


struct ErrorManager
{
    [[nodiscard]] void StoreError(int16_t error)
    {
	nError=error;
    }
    [[nodiscard]] void GetError(int16_t error) 
    {
	return nError;
    }
    private:
	int16_t nError;


}
