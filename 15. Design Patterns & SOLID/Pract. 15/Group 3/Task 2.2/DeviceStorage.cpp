#include "DeviceStorage.h"

const size_t INITIAL_CAPACITY = 16;

DeviceStorage& DeviceStorage::getInstance()
{
    static DeviceStorage instance;
    return instance;
}

void DeviceStorage::addDevice(ElectronicDevice* device)
{
    if (devicesCount == capacity) {
        resize(capacity * 2);
    }
    devices[devicesCount++] = device;
    // takes ownership of device
}

void DeviceStorage::addDevice(const ElectronicDevice& device)
{
    addDevice(device.clone());
}

void DeviceStorage::addDevice(DeviceType deviceType)
{
    addDevice(ElectronicDeviceFactory::getInstance().createElectronicDevice(deviceType));
}

void DeviceStorage::addDevice(DeviceType deviceType, const char* model, double price, const char* param)
{
    addDevice(ElectronicDeviceFactory::getInstance().createElectronicDevice(deviceType, model, price, param));
}

void DeviceStorage::removeDevice(size_t index)
{
    if (index >= devicesCount) {
        throw std::out_of_range("Index out of range!");
    }

    delete devices[index];
    for (size_t i = index; i < devicesCount - 1; i++) {
        devices[i] = devices[i + 1];
    }
    --devicesCount;
}

const ElectronicDevice* DeviceStorage::operator[](size_t index) const
{
    return devices[index];
}

size_t DeviceStorage::getDevicesCount() const
{
    return devicesCount;
}

DeviceStorage::DeviceStorageIterator DeviceStorage::begin()
{
    return DeviceStorageIterator(devices);
}

DeviceStorage::DeviceStorageIterator DeviceStorage::end()
{
    return DeviceStorageIterator(devices + devicesCount);
}

DeviceStorage::DeviceStorage() : capacity(INITIAL_CAPACITY), devicesCount(0)
{
    devices = new ElectronicDevice * [capacity];
}

DeviceStorage::~DeviceStorage()
{
    free();
}

void DeviceStorage::resize(size_t newCapacity)
{
    ElectronicDevice** resizedDevices = new ElectronicDevice * [newCapacity];
    for (size_t i = 0; i < devicesCount; i++) {
        resizedDevices[i] = devices[i];
    }
    delete[] devices;
    devices = resizedDevices;
    capacity = newCapacity;
}

void DeviceStorage::free()
{
    for (size_t i = 0; i < devicesCount; i++) {
        delete devices[i];
    }
    delete[] devices;
    devices = nullptr;
    devicesCount = capacity = 0;
}

DeviceStorage::DeviceStorageIterator::DeviceStorageIterator(ElectronicDevice** ptr) : current(ptr) {}

ElectronicDevice* DeviceStorage::DeviceStorageIterator::operator*() const
{
    return *current;
}

DeviceStorage::DeviceStorageIterator& DeviceStorage::DeviceStorageIterator::operator++()
{
    ++current;
    return *this;
}

DeviceStorage::DeviceStorageIterator& DeviceStorage::DeviceStorageIterator::operator--()
{
    --current;
    return *this;
}

bool DeviceStorage::DeviceStorageIterator::operator==(const DeviceStorageIterator& other) const
{
    return current == other.current;
}

bool DeviceStorage::DeviceStorageIterator::operator!=(const DeviceStorageIterator& other) const
{
    return current != other.current;
}
