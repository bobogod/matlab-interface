/*
------------------------------------------------------------------

This file is part of the Open Ephys GUI
Copyright (C) 2019 Open Ephys

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include "MatlabInterfaceEditor.h"
#include "MatlabInterface.h"

ConnectionViewer::ConnectionViewer(MatlabInterface* parentNode) : 
	Component(), Thread("ConnectionViewer"),
	interface(parentNode) 
{

	width = 100;
	height = 200;
	buttonSize = 50;

	setSize(width, height);
	setColour(ColourSelector::backgroundColourId, Colours::transparentBlack);

	isConnected = interface->connect();

};

ConnectionViewer::~ConnectionViewer() 
{

};

void ConnectionViewer::buttonClicked(Button* button) {};

void ConnectionViewer::run()
{

	LOGC("Waiting for connection...");
	

}

MatlabInterfaceEditor::MatlabInterfaceEditor(MatlabInterface* parentNode)
	: GenericEditor(parentNode)

{

	interface = parentNode;

	desiredWidth = 230;

	addTextBoxParameterEditor("host_address", 10, 25);

	addTextBoxParameterEditor("port_number", 115, 25);

	connectButton = std::make_unique<UtilityButton>("Connect", Font("Small Text", 13, Font::bold));
	connectButton->setRadius(3.0f);
	connectButton->setBounds(70, 75, 90, 20);
	connectButton->addListener(this);
	addAndMakeVisible(connectButton.get());

	addSelectedChannelsParameterEditor("Channel", 75, 100);

	count = 0;
}

MatlabInterfaceEditor::~MatlabInterfaceEditor()
{

}


void MatlabInterfaceEditor::buttonClicked(Button* button)
{
	
	viewer = new ConnectionViewer(interface);

	if (viewer->isConnected)
	{
		connectButton->setEnabled(false);
	}

	CoreServices::updateSignalChain(this);
}


