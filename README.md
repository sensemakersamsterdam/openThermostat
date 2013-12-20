# openThermostat
openThermostat is an Open (source) Thermostat design consisting of both hardware and software which offers basic functionality that can be used as a base for every Maker or DIYer to expand upon.

The current version is implemented as an Arduino shield.


# Getting started
To get started you can either [download everything](https://github.com/sensemakersamsterdam/openThermostat/archive/master.zip) in this repository or clone it with `git clone https://github.com/sensemakersamsterdam/openThermostat.git`.
Additionally to get the wiki documentation run `git submodule init` and `git submodule update`.

The repository contains the following files/folders:
* firmware: Arduino sketch to compile and upload to the Arduino the shield is mounted on
  * display_test: Documented code to test the display
  * temp_test: Documented code to test the DS18B20 temperature sensor
* PCB: EAGLE Schematic and PCB layout files as well as exports to PDF and DXF
  * pictures: PNG pictures from the PCB layout and schematic
* wiki: the contents of the openThermostat wiki repository.

More details about building an openThermostatShield and about using the Arduino sketches can be found on the [openThermostatShield wiki page](../../wiki/openThermostatShield).


# Contributing
If you want to contribute feel free to fork the repository, add your changes and send us a pull request. We'd be happy to accept your contributions.
Make your changes in a new branch and please include documentation (using the wiki) for new features and major changes in the pull request.
