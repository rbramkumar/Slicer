/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Brigham and Women's Hospital

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qMRMLSequenceBrowserToolBarPlugin_h
#define __qMRMLSequenceBrowserToolBarPlugin_h

#include "qSlicerSequencesModuleWidgetsAbstractPlugin.h"

class Q_SLICER_MODULE_SEQUENCES_WIDGETS_PLUGINS_EXPORT
qMRMLSequenceBrowserToolBarPlugin
  : public QObject, public qSlicerSequencesModuleWidgetsAbstractPlugin
{
  Q_OBJECT

public:
  qMRMLSequenceBrowserToolBarPlugin(QObject *_parent = 0);

  QWidget *createWidget(QWidget *_parent);
  QString  domXml() const;
  QIcon    icon() const;
  QString  includeFile() const;
  bool     isContainer() const;
  QString  name() const;

};

#endif
