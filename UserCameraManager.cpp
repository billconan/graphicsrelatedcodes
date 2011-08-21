#include "UserCameraManager.h"
#include <QtGui/QMenu>
#include "DynamicAction.h"

UserCameraManager::UserCameraManager(void)
{
}

UserCameraManager::~UserCameraManager(void)
{
	std::vector<Camera *>::iterator iter=userCameraList.begin();
	for(;iter!=userCameraList.end();)
	{
		std::vector<Camera *>::iterator toBeDeleted=iter++;
		delete *toBeDeleted;
	}
}

int UserCameraManager::addCamera(Camera *camera)
{
	int cameraID=userCameraList.size();
	userCameraList.push_back(camera);
	emit onCameraAdded(cameraID);
	return cameraID;
}

//ɾ����Ӱ����ʱ����������Ӱ����ʹ�ã��ǾͲ����ˡ�Ҫע�⡣
void UserCameraManager::removeCamera(Camera *camera)
{
	std::vector<Camera *>::iterator iter=userCameraList.begin();
	for(;iter!=userCameraList.end();++iter)
	{
		if((*iter)==camera)
		{
			userCameraList.erase(iter);
			delete camera;
			break;
		}
	}
}

Camera * UserCameraManager::getCameraByID(int id)
{
	if(id>=0 && id<userCameraList.size())
	{
		return userCameraList[id];
	}
	else
	{
		return 0;
	}
}


void UserCameraManager::setUserCameraMenu(QMenu &menu)
{
	menu.clear();

	for(int i=0;i<userCameraList.size();++i)
	{
		DynamicAction *aCameraAction=new DynamicAction(&menu);
		aCameraAction->setText(userCameraList[i]->cameraName());
		aCameraAction->setData(QVariant(i));

		menu.addAction(aCameraAction);
	}
}

std::vector<Camera *> & UserCameraManager::getCameraList()
{
	return userCameraList;
}