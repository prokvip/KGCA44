#include "TMapObj.h"
#include "TDevice.h"
void TMapObj::SetVertexData()
{
	TObject::SetVertexData();
	float xSize = 152;
	float ySize = 768;
	TRect rt = { 90.0f, 1.0f, 132.0f, 61.0f };
	m_vVertexList[0].t = { 0.0f,0.0f };
	m_vVertexList[1].t = { 1.0f,0.0f };
	m_vVertexList[2].t = { 0.0f,140.0f / ySize };
	m_vVertexList[3].t = { 1.0f,140.0f / ySize };
}