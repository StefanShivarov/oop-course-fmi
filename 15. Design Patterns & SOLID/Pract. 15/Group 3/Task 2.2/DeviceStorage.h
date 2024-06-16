#pragma once
#include "ElectronicDevice.h"
#include "ElectronicDeviceFactory.h"

class DeviceStorage
{
public:
    DeviceStorage(const DeviceStorage& other) = delete;
    DeviceStorage& operator=(const DeviceStorage& other) = delete;

    static DeviceStorage& getInstance();

    void addDevice(ElectronicDevice* device);
    void addDevice(const ElectronicDevice& device);
    void addDevice(DeviceType deviceType);
    void addDevice(DeviceType deviceType, const char* model, double price, const char* param);

    void removeDevice(size_t index);

    const ElectronicDevice* operator[](size_t index) const;
    size_t getDevicesCount() const;

    class DeviceStorageIterator
    {
    public:
        DeviceStorageIterator(ElectronicDevice** ptr);

        ElectronicDevice* operator*() const;

        DeviceStorageIterator& operator++();
        DeviceStorageIterator& operator--();

        bool operator==(const DeviceStorageIterator& other) const;
        bool operator!=(const DeviceStorageIterator& other) const;
    private:
        ElectronicDevice** current;
    };

    DeviceStorageIterator begin();
    DeviceStorageIterator end();
private:
    ElectronicDevice** devices;
    size_t devicesCount;
    size_t capacity;
        
    DeviceStorage();
    ~DeviceStorage();

    void resize(size_t newCapacity);
    void free();
    // no need for copyFrom and moveFrom since the storage is singleton and cannot be copied!
};

