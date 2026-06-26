#include "stdafx.h"
#include <new>




using namespace std;

static std::unordered_map<void*, size_t>& DynamicArrayElementCounts() {
	// Kept alive until process shutdown because static destructors can still
	// unregister dynamic arrays after ordinary function-local statics are gone.
	static std::unordered_map<void*, size_t>* dynamicArrayElementCounts = new std::unordered_map<void*, size_t>();
	return *dynamicArrayElementCounts;
}

static size_t EffectiveDimension(int configuredDimension, size_t fallbackDimension) {
	return configuredDimension > 0 ? (size_t)configuredDimension : fallbackDimension;
}

void RegisterDynamicArray(void* variable, size_t elements) {
	if (variable != nullptr) {
		DynamicArrayElementCounts()[variable] = elements;
	}
}

static char* allocateCharArray(size_t dimension, const char* source) {
	if (dimension == 0) {
		dimension = 1;
	}
	char* dynamicArray = new (std::nothrow) char[dimension];
	if (dynamicArray == nullptr) {
		return nullptr;
	}
	RegisterDynamicArray(dynamicArray, dimension);
	std::memset(dynamicArray, '\0', dimension);
	if (source != nullptr && dimension > 1) {
		std::strncpy(dynamicArray, source, dimension - 1);
		dynamicArray[dimension - 1] = '\0';
	}
	return dynamicArray;
}

size_t GetDynamicArraySize(const void* variable) {
	if (variable == nullptr) {
		return 0;
	}
	auto& dynamicArrayElementCounts = DynamicArrayElementCounts();
	auto found = dynamicArrayElementCounts.find(const_cast<void*>(variable));
	if (found == dynamicArrayElementCounts.end()) {
		return 0;
	}
	return found->second;
}

void UnregisterDynamicArray(void* variable) {
	if (variable != nullptr) {
		DynamicArrayElementCounts().erase(variable);
	}
}

template <typename T>
static void clearDynamicArray(T* variable, size_t elements) {
	if (variable != nullptr) {
		for (size_t i = 0; i < elements; ++i) {
			variable[i] = T(0);
		}
	}
}

static void clearDynamicArray(char* variable, size_t elements) {
	if (variable != nullptr && elements > 0) {
		std::memset(variable, '\0', elements);
	}
}

static void clearDynamicArray(bool* variable, size_t elements) {
	if (variable != nullptr) {
		for (size_t i = 0; i < elements; ++i) {
			variable[i] = false;
		}
	}
}

static void clearDynamicArray(PrecisionValue* variable, size_t elements) {
	if (variable != nullptr) {
		for (size_t i = 0; i < elements; ++i) {
			variable[i] = (higherPrecision == 1) ? PrecisionValue(mp_float(0)) : PrecisionValue(0.0);
		}
	}
}

void Created(const char* variableName, char* variableData) {
	if (mainRoutine && manageDynamicAllocations) {
		DynamicAllocationData dynamic = DynamicAllocationData();
		if (variableData == nullptr) {
			dynamic.data = "<null>";
		}
		else {
			const size_t maxLogLength = 512;
			size_t dataLength = std::strlen(variableData);
			dynamic.data = dataLength > maxLogLength ? std::string(variableData, maxLogLength) + "..." : variableData;
		}
		dynamic.name = variableName ? variableName : "";
		dynamicAllocation.addObject(dynamic);
	}
}

void Deleted(const char* variableName) {
	if (mainRoutine && manageDynamicAllocations && variableName != nullptr) {
		if (dynamicAllocation.getPosition(variableName) < (int)dynamicAllocation.getCount()) {
			dynamicAllocation.removeObject(variableName);
		}
	}
}


void CheckForNotDeleted() {
	if (mainRoutine && manageDynamicAllocations && dynamicAllocation.getCount() > 0) {
		for (int i = 0; i < (int)dynamicAllocation.getCount(); i++) {

			DynamicAllocationData dynamic = dynamicAllocation.getObject(i);
			printf("\n Variable-> %s  variableData-> %s \n", dynamic.name.c_str(), dynamic.data.c_str());
		}
	}

}



char* getDynamicCharArray(char* source, const char* variable) {
	size_t dimension = EffectiveDimension(DIM, 3100);
	char* dynamicArray = allocateCharArray(dimension, source);
	if (dynamicArray != nullptr && mainRoutine && manageDynamicAllocations) {
		Created(variable, source);
	}
	return dynamicArray;
}

char* getDynamicCharArray(int level, char* source, const char* variable) {
	// level kept for backward compatibility.
	size_t dimension = EffectiveDimension(DIM, 3100);
	char* dynamicArray = allocateCharArray(dimension, source);
	if (dynamicArray != nullptr && mainRoutine && manageDynamicAllocations) {
		Created(variable, source);
	}
	return dynamicArray;
}

char* getDynamicCharArrayLong(char* source) {
	size_t dimension = EffectiveDimension(LONGDIM, 3100);
	char* dynamicArray = allocateCharArray(dimension, source);
	if (dynamicArray != nullptr && mainRoutine && manageDynamicAllocations) {
		Created("long variable", source);
	}
	return dynamicArray;
}



char* getDynamicCharArrayShort(char* source, const char* variable) {
	size_t dimension = EffectiveDimension(SHORTDIM, 3100);
	char* dynamicArray = allocateCharArray(dimension, source);
	if (dynamicArray != nullptr && mainRoutine && manageDynamicAllocations) {
		Created(variable, source);
	}
	return dynamicArray;
}
PrecisionValue** getDynamic2DDoubleArray() {
	if (DIMTWOD <= 0 || DIMDOUBLE <= 0) {
		return nullptr;
	}
	PrecisionValue** dynamicArray = new (std::nothrow) PrecisionValue * [DIMTWOD];
	if (dynamicArray == nullptr) {
		return nullptr;
	}
	RegisterDynamicArray(dynamicArray, DIMTWOD);
	for (size_t i = 0; i < (size_t)DIMTWOD; ++i) {
		dynamicArray[i] = nullptr;
	}

	for (size_t i = 0; i < (size_t)DIMTWOD; ++i) {
		dynamicArray[i] = new (std::nothrow) PrecisionValue[DIMDOUBLE];
		if (dynamicArray[i] == nullptr) {
			for (size_t j = 0; j < i; ++j) {
				clearDynamicArray(dynamicArray[j], (size_t)DIMDOUBLE);
				UnregisterDynamicArray(dynamicArray[j]);
				delete[] dynamicArray[j];
				dynamicArray[j] = nullptr;
			}
			UnregisterDynamicArray(dynamicArray);
			delete[] dynamicArray;
			return nullptr;
		}
		RegisterDynamicArray(dynamicArray[i], DIMDOUBLE);
		for (size_t j = 0; j < (size_t)DIMDOUBLE; ++j) {
			dynamicArray[i][j] = (higherPrecision == 1) ? PrecisionValue(mp_float(0)) : PrecisionValue(0.0);
		}
	}
	return dynamicArray;
}
// Função para eliminar matrizes dinâmicas 2D de T
template <typename T>
void _Delete(T**& variable, int lines, char* variableName) {
	if (variable != nullptr) {
		size_t actualLines = lines > 0 ? (size_t)lines : (size_t)DIMTWOD;
		for (size_t i = 0; i < actualLines; ++i) {
			if (variable[i] != nullptr) {
				size_t elements = GetDynamicArraySize(variable[i]);
				if (elements > 0) {
					clearDynamicArray(variable[i], elements);
				}
				UnregisterDynamicArray(variable[i]);
				delete[] variable[i];
				variable[i] = nullptr;
			}
		}

		UnregisterDynamicArray(variable);
		delete[] variable;

		if (mainRoutine && manageDynamicAllocations) {
			Deleted(variableName);
		}
		variable = nullptr;
	}
}

template <typename T>
static void releaseDynamicArray(T*& variable, const char* variableName) {
	if (variable == nullptr) {
		return;
	}
	if (mainRoutine && manageDynamicAllocations) {
		Deleted(variableName);
	}
	size_t elements = GetDynamicArraySize(variable);
	if (elements > 0) {
		clearDynamicArray(variable, elements);
	}
	UnregisterDynamicArray(variable);
	delete[] variable;
	variable = nullptr;
}

template <typename T>
void _delete(T*& variable, char* variableName) {
	releaseDynamicArray(variable, variableName);
}

void _delete(int*& variable, char* variableName) {
	releaseDynamicArray(variable, variableName);
}
void _delete(bool*& variable, char* variableName) {
	releaseDynamicArray(variable, variableName);
}

void _delete(char*& variable, const char* variableName) {
	releaseDynamicArray(variable, variableName);
}



void _deleteLong(char*& variable, const char* variableName) {
	releaseDynamicArray(variable, variableName != nullptr ? variableName : "long variable");
}

void _deleteShort(char*& variable, const char* variableName) {
	releaseDynamicArray(variable, variableName);
}
template <typename T>
void _Delete(T**& variable, int lines, int columns, char* variables) {
	if (variable == nullptr) {
		return;
	}
	size_t actualLines = lines > 0 ? (size_t)lines : (size_t)DIMTWOD;
	for (size_t i = 0; i < actualLines; ++i) {
		if (variable[i] != nullptr) {
			size_t elements = GetDynamicArraySize(variable[i]);
			if (elements == 0 && columns > 0) {
				elements = (size_t)columns;
			}
			if (elements > 0) {
				clearDynamicArray(variable[i], elements);
			}
			UnregisterDynamicArray(variable[i]);
			delete[] variable[i];
			variable[i] = nullptr;
		}
	}
	UnregisterDynamicArray(variable);
	delete[] variable;
	if (mainRoutine && manageDynamicAllocations) {
		Deleted(variables);
	}
	variable = nullptr;
}
void _Delete(char**& variable, int lines, int columns, char* variables) {
	if (variable == nullptr) {
		return;
	}
	size_t actualLines = lines > 0 ? (size_t)lines : (size_t)DIMTWOD;
	for (size_t i = 0; i < actualLines; ++i) {
		if (variable[i] != nullptr) {
			size_t elements = GetDynamicArraySize(variable[i]);
			if (elements == 0 && columns > 0) {
				elements = (size_t)columns;
			}
			if (elements > 0) {
				clearDynamicArray(variable[i], elements);
			}
			UnregisterDynamicArray(variable[i]);
			delete[] variable[i];
			variable[i] = nullptr;
		}
	}
	UnregisterDynamicArray(variable);
	delete[] variable;
	if (mainRoutine && manageDynamicAllocations) {
		Deleted(variables);
	}
	variable = nullptr;
}


char* getDynamicCharArrayFixedLength(const char* source, size_t length) {
	return allocateCharArray(length, source);
}

char* getDynamicCharArrayFixedLenght(const char* source, size_t length) {
	return getDynamicCharArrayFixedLength(source, length);
}

char* getRenewDynamicCharArray(char* source, char** oldPointer) {
	if (oldPointer != nullptr) {
		_delete(*oldPointer, "*oldPointer");
	}
	size_t dimension = EffectiveDimension(DIM, 3100);
	char* ptr = allocateCharArray(dimension, source);
	if (oldPointer != nullptr) {
		*oldPointer = ptr;
	}
	return ptr;
}

char* getRenewDynamicCharArrayFixedLength(char* source, char** oldPointer, int size) {
	if (oldPointer == nullptr) {
		return getDynamicCharArrayFixedLength(source, size > 0 ? (size_t)size : 1);
	}
	if (*oldPointer != nullptr) {
		_delete(*oldPointer, "*oldPointer");
	}
	*oldPointer = getDynamicCharArrayFixedLength(source, size > 0 ? (size_t)size : 1);
	return *oldPointer;
}

char* getCorrectedDynamicCharArray(char** charArrayPointer) {
	if (charArrayPointer == nullptr) {
		return nullptr;
	}
	char* data = *charArrayPointer;
	char* newCharArray = getDynamicCharArray("", "newCharArray");
	if (newCharArray == nullptr) {
		return nullptr;
	}
	size_t dimension = EffectiveDimension(DIM, 3100);
	size_t copyLength = data ? std::min(std::strlen(data), dimension - 1) : 0;
	if (copyLength > 0) {
		std::memcpy(newCharArray, data, copyLength);
	}
	newCharArray[dimension - 1] = '\0';
	_delete(*charArrayPointer, "* charArrayPointer");
	*charArrayPointer = newCharArray;
	return *charArrayPointer;
}
int* getDynamicIntArray() {
	size_t size = EffectiveDimension(DIM, 3100);
	int* dynamicArray = new (std::nothrow) int[size];
	if (dynamicArray == nullptr) {
		return nullptr;
	}
	RegisterDynamicArray(dynamicArray, size);
	std::fill(dynamicArray, dynamicArray + size, 0);
	return dynamicArray;
}


template void _Delete<PrecisionValue>(PrecisionValue**&, int, char*);
template void _Delete<PrecisionValue>(PrecisionValue**&, int, int, char*);
template void _Delete<double>(double**&, int, int, char*);
template void _delete<double>(double*&, char*);
template void _delete<mp_float>(mp_float*&, char*);
