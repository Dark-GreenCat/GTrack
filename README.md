# 🗺️ Welcome to GTrack Project

This project aims to develop a multi-layered software architecture using a Hardware Abstraction Layer (HAL) library to control a GPS tracking device called GTrack. A 5-layer module structure will be implemented to separate the software into distinct components handling different functional aspects of GPS data acquisition and device control. The goal is to make GTrack capable of obtaining location data, including coordinates and direction, for as long a period and as accurately as possible through this modularized approach. The HAL library will allow the software to interface with the GPS hardware in a standardized way across the various layers.


# 📑Project Structure

The software modules for this project will be organized within a project source code folder structure. Specifically, each module will be written inside a 'Src' folder.

Within the Src folder, the modules will be further separated into 4 sub-folders based on their corresponding layer/functionality:

## 📂 HCL (Hardware Communication Layer)

This folder will contain data structures and functions that enable low-level communication with the GPS hardware interfaces. This layer handles all interactions with the device peripherals.

## 📂 PCL (Peripheral Controller Layer)

The PCL folder houses functions developed to control GPS sensor devices and peripherals via calls to the HCL's interfaces. It builds upon HCL to provide device control capabilities.

## 📂 NAL (Network Application Layer)

This layer, coded within the NAL folder, contains functions that allow the software to access any network-based features via calls to lower layers.

## 📂 UAL (User Application Layer)

As the highest layer, the UAL folder holds code implementing user-facing system features and behavior through interfaces beneath it. These functions deliver the program's intended purpose to the end-user.

## 📌 Notes

The layers are structured such that a module may call functionality from a lower layer module (i.e. the layer directly beneath it). A module may also access functions within its own layer. However, no module should directly invoke interfaces belonging to a higher layer; this strict layering scheme helps enforce separation of concerns.

The folder organization and layer dependencies aim to provide a clear and maintainable software architecture for developing the GPS tracking capabilities of the GTrack device. Let me know if any part of the structure or intentions need further elaboration.
