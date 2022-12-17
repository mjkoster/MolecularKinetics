# Molecular Kinetics Project

## Overview

Open source project to provide modular O2 generation capacity in the commercially underserved range between 0.1 and 2 mtpd.

## Deliverables
- A reference unit using conventional PSA architecture scaled to 15 slpm capacity, modeled after the Oxikit project.
- A protoype/pilot "system slice" module using VPSA architecture scaled to 25 slpm. The target throughput for full scale units to ~150 slpm
- A test stand with a 500g column for small scale experimental validation
- P&I diagrams
- Schematics and PCB layouts for RTUs, and control wiring diagrams
- Open source framework for control software https://github.com/mjkoster/ObjectFlow

## Status:

- The test stand is assembled and ready for filling and testing
- The PSA reference unit is 95%+ assembled. Left to do is terminate the wiring at RTU and equipment ends
- The VPSA prototype slice is 80% assembled. Left to do is O2 plmbing, control box assembly, chassis wiring, column internals
- Control software based on https://github.com/mjkoster/ObjectFlow.

## VPSA system slice module

- System slice has all of the components to build a modular, scalable system by adding more slices.
- Prototype slice is 25 slpm, full scale units will be 50-150 slpm per slice
- Prototype has a 4-valve system and a reversible pump, full scale units use reversible pump with a blowdown valve
- Minimal need for local experts, autonomous operation and simple periodic maintenance, connected to a central admin
- Very simple architecture and construction, common parts used in automotive, dairy, beverage industries
- Robust construction, long service life
- Superior maintainability

## The concept for the PSA unit:

An open source oxygen generator designed to deliver 10-20 liters per minute of medical grade oxygen.

### Highlights:
* PSA air separator with design parameters in the same range as [Oxikit](https://oxikit.com/) 
* Incorporates a silica-based air dryer using TSA to regenerate
* Highly serviceable using common tools and skills
* All-metal construction with tri-clamp and SAE flare service connections
* Built mostly from commonly available components with some easily-fabricated brackets and mounting plates
* Uses a standard 19 inch electronics rack as the central mounting frame
* Research unit with additional monitor and control points
* Control system using model-driven approach and rapid prototyping
* Network connection to enable remote management and diagnostics

### Package contents:
* High level documentation and images for the assembled system and sub-components
* BOM and component specifications
* Design/CNC files for the fabricated components
* Schematics and PCB fabrication files
* Control system models and code generators for Arduino and Node-RED modules
* Arduino framework code for RTUs
* Node-RED framework code for PLC Brain
* Pre-built runnable code for the full prototype system

