/*
 *  Copyright 2011, 2012, DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#ifdef _PRINT_HEADER_
#warning "SensorHandler.h"
#endif

#include <main_gui/PropertyDialog.h>
#include <interfaces/sim/ControlCenter.h>
#include <interfaces/core_objects_exchange.h>
#include <interfaces/sensor_bases.h>
#include "SelectionDialog.h"

namespace mars {
  namespace gui {

    namespace SensorTree {

      enum Mode {
        PreviewMode,
        EditMode
      };

    }

    class SensorHandler : public QObject {
      Q_OBJECT
      public:

      SensorHandler(QtVariantProperty *property, unsigned long ind,
                    main_gui::PropertyDialog *pd, interfaces::ControlCenter *c, 
                    SensorTree::Mode m);
      ~SensorHandler();

      void valueChanged(QtProperty *property, const QVariant &value);
      void focusIn();
      void focusOut();
      void accept();

      SensorTree::Mode mode;

    public slots:
      void choose_nodes(QString list);
      void choose_joints(QString list);
      void choose_motors(QString list);
      void selection();

 
    private:  
      MarsVector<interfaces::core_objects_exchange> myMotors;
      MarsVector<interfaces::core_objects_exchange> myNodes;
      MarsVector<interfaces::core_objects_exchange> myJoints;
      MarsVector<interfaces::core_objects_exchange> chosenOnes;
      interfaces::ControlCenter *control;
  
      interfaces::BaseSensor *mySensor;
      bool filled;
      QtVariantProperty* type, *name, *update_rate, *objects;
      SelectionDialog* nodeDialog, *jointDialog, *motorDialog; 
 
      QtVariantProperty *topLevelSensor;

      MarsVector<interfaces::core_objects_exchange> allSensors;
      std::string sensorName;
      std::string actualName;
      int mySensorIndex;
      main_gui::PropertyDialog *pDialog;
      QColor previewColor;
      QColor editColor;

  
      void fill();
      void on_change_type(int index);
      void updateSensor();
 

    };


  } // end of namespace gui
} // end of namespace mars

#endif // SENSOR_HANDLER_H
