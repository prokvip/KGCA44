#include "TWorld.h"
void TWorld::AddCollisionExecute(
	TObject* pOwner,
	CollisionFunction fun)
{
	pOwner->m_iCollisionID = ++m_iExecuteCollisionID;
	m_ObjectList.insert(std::make_pair(
		pOwner->m_iCollisionID,
		pOwner));
	m_fnCollisionExecute.insert(std::make_pair(
		pOwner->m_iCollisionID,
		fun));

	/*auto iter = m_fnCollisionExecute.find(
		pOwner->m_iCollisionID);
	if (iter != m_fnCollisionExecute.end())
	{
		CollisionFunction call = iter->second;
		call(nullptr, 999);
	}*/
}
void TWorld::DeleteCollisionExecute(TObject* pOwner)
{
	auto iter = m_ObjectList.find(pOwner->m_iCollisionID);
	if (iter != m_ObjectList.end())
	{
		m_ObjectList.erase(iter);
	}
	auto iterFun = m_fnCollisionExecute.find(pOwner->m_iCollisionID);
	if (iterFun != m_fnCollisionExecute.end())
	{
		m_fnCollisionExecute.erase(iterFun);
	}
}
void   TWorld::Frame()
{
	for (auto src : m_ObjectList)
	{
		TObject* pSrcObj = src.second;
		if (pSrcObj->m_bDead) continue;
		for (auto dest : m_ObjectList)
		{
			if (src == dest) continue;			
			TObject* pDestObj = dest.second;
			if (pDestObj->m_bDead) continue;
			if (TCollision::CheckSphereToSphere(
				pSrcObj->m_Sphere,
				pDestObj->m_Sphere))
			{
				auto iter = m_fnCollisionExecute.find(
					pSrcObj->m_iCollisionID);
				if (iter != m_fnCollisionExecute.end())
				{
					CollisionFunction call = iter->second;
					call(pDestObj, 999);
				}
			}
		}
	}
}