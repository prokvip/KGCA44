#include "TMapObj.h"
#include "TDevice.h"
#include <time.h>
void TMapMeshRender::SetVertexData()
{
	m_vVertexList.resize(m_iNumRow * m_iNumCol);
	m_vScreenList.resize(m_iNumRow * m_iNumCol);
	m_Cells.resize(m_iNumCellRow * m_iNumCellCol);
	// 0  1  2  
	// 3  4  5 
	// 6  7  8
	// iNumCell  = (3-1) * (3-1)
	float fOffsetU = 1.0f / (float)m_iNumCellCol;
	float fOffsetV = 1.0f / (float)m_iNumCellRow;
	for (UINT iRow = 0; iRow < m_iNumRow; iRow++)
	{
		for (UINT iCol = 0; iCol < m_iNumCol; iCol++)
		{
			float x = iCol * m_vCellDistance.x;
			float y = iRow * m_vCellDistance.y;
			m_vScreenList[iRow * m_iNumRow + iCol].x = m_rtScreen.v1.x + x;
			m_vScreenList[iRow * m_iNumRow + iCol].y = m_rtScreen.v1.y + y;
			m_vVertexList[iRow * m_iNumRow + iCol].v = ScreenToNDC(x, y, g_ptClientSize);
			m_vVertexList[iRow * m_iNumRow + iCol].c = { iCol / 2.0f, iRow / 2.0f, 1.0f,1.0f };
			m_vVertexList[iRow * m_iNumRow + iCol].t.x = iCol;
			m_vVertexList[iRow * m_iNumRow + iCol].t.y = iRow;
		}
	}
}
void TMapMeshRender::SetIndexData()
{
	m_vIndexList.resize(m_iNumIndex);
	// 0  1  2  
	// 3  4  5 
	// 6  7  8
	// iNumCell  = (3-1) * (3-1)

	UINT iIndex = 0;
	for (UINT iRowCell = 0; iRowCell < m_iNumCellRow; iRowCell++)
	{
		for (UINT iColCell = 0; iColCell < m_iNumCellCol; iColCell++)
		{
			UINT iNextCol = iColCell + 1;
			UINT iNextRow = iRowCell + 1;
			m_vIndexList[iIndex + 0] = iRowCell * m_iNumCol + iColCell;
			m_vIndexList[iIndex + 1] = iRowCell * m_iNumCol + iNextCol;
			m_vIndexList[iIndex + 2] = iNextRow * m_iNumCol + iColCell;

			m_vIndexList[iIndex + 3] = m_vIndexList[iIndex + 2];
			m_vIndexList[iIndex + 4] = m_vIndexList[iIndex + 1];
			m_vIndexList[iIndex + 5] = iNextRow * m_iNumCol + iNextCol;

			UINT iCell = iRowCell * m_iNumCellCol + iColCell;
			float x1 = m_vScreenList[m_vIndexList[iIndex + 0]].x;
			float y1 = m_vScreenList[m_vIndexList[iIndex + 0]].y;
			float x2 = m_vScreenList[m_vIndexList[iIndex + 5]].x;
			float y2 = m_vScreenList[m_vIndexList[iIndex + 5]].y;
			m_Cells[iCell].rt.SetP(x1, y1, x2, y2);
			m_Cells[iCell].iTexID = 0;
			iIndex += 6;
		}
	}	
}
void TMapMeshRender::PreRender()
{
	TDevice::m_pd3dContext->PSSetShaderResources(
		0, 1, &m_pTexture->m_pTexSRV);
	TDevice::m_pd3dContext->VSSetShader(
		m_pShader->m_pVertexShader.Get(), nullptr, 0);
	TDevice::m_pd3dContext->PSSetShader(
		m_pShader->m_pPixelShader.Get(), nullptr, 0);
	TDevice::m_pd3dContext->IASetInputLayout(
		m_pInputLayout->Get());

	// 정점버퍼에서 Offsets에서 시작하여
	// Strides크기로 정점을 정점쉐이더로 전달해라.
	UINT Strides = sizeof(PCT_VERTEX);
	UINT Offsets = 0;
	TDevice::m_pd3dContext->IASetVertexBuffers(
		0,
		1,
		m_pVertexBuffer.GetAddressOf(),
		&Strides,
		&Offsets);
	TDevice::m_pd3dContext->IASetIndexBuffer(
		m_pIndexBuffer.Get(),
		DXGI_FORMAT_R32_UINT, 0);
	TDevice::m_pd3dContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
void TMapMeshRender::PostRender()
{
	if (m_pIndexBuffer == nullptr)
		TDevice::m_pd3dContext->Draw(m_vVertexList.size(), 0);
	else
	{
		srand(time(NULL));
		for (int iCell = 0; iCell < m_iNumCellRow * m_iNumCellCol; iCell++)
		{
			UINT iTex = m_Cells[iCell].iTexID;// rand() % 4;
			TDevice::m_pd3dContext->PSSetShaderResources(
				0, 1, &m_pTexs[iTex]->m_pTexSRV);
			TDevice::m_pd3dContext->DrawIndexed(6, 6 * iCell, 0);
		}
	}
}

TMapObj::TMapObj()
{
}
TMapObj::TMapObj(UINT iCellX, UINT iCellY)
{
	SetCellCounter(iCellX, iCellY);
	m_rtScreen.SetS(0.0f, 0.0f, (float)g_ptClientSize.x, (float)g_ptClientSize.y );
	m_vCellDistance.x = (float)g_ptClientSize.x / (float)m_iNumCellCol;
	m_vCellDistance.y = (float)g_ptClientSize.y / (float)m_iNumCellRow;
}
TMapObj::TMapObj(TRect rt, UINT iCellX, UINT iCellY)
{
	m_rtScreen = rt;
	m_vCellDistance = (rt.v2 - rt.v1) / iCellX;
	SetCellCounter(iCellX, iCellY);
}
bool	TMapObj::Create(TWorld* pWorld)
{
	m_pWorld = pWorld;
	m_pMeshRender = std::make_shared<TMapMeshRender>();
	m_pMeshRender->Create();
	m_pTexs[0] = I_Tex.Load(L"../../data/texture/gg.bmp");
	m_pTexs[1] = I_Tex.Load(L"../../data/texture/kgcalogo.bmp");
	m_pTexs[2] = I_Tex.Load(L"../../data/texture/kgca08.bmp");
	m_pTexs[3] = I_Tex.Load(L"../../data/texture/black.bmp");
	return true;
}
void TMapObj::Frame()
{
	//srand(time(NULL));
	//UINT iVertex = rand() % m_vVertexList.size();
	///*for (int i = 0; i < m_vVertexList.size(); i++)
	//{
	//	m_vVertexList[i].v.x += g_fSPF * cosf(g_fGT);
	//}*/

	//static float vPos = 0.0f;
	//static float tEnd = 1000.0f;
	//vPos += g_fSPF * 0.0f;
	//tEnd   += g_fSPF * 0.0f;
	//UINT xSize = m_pTexture->m_TexDesc.Width;
	//UINT ySize = m_pTexture->m_TexDesc.Height;
	//m_vVertexList[0].t = { 0.0f,vPos / ySize };
	//m_vVertexList[1].t = { 1.0f,vPos / ySize };
	//m_vVertexList[2].t = { 0.0f,tEnd / ySize };
	//m_vVertexList[3].t = { 1.0f,tEnd / ySize };
	///*m_vVertexList[0].t = { vPos / xSize, 0.0f };
	//m_vVertexList[1].t = { tEnd / xSize, 0.0f };
	//m_vVertexList[2].t = { vPos / xSize, 1.0f };
	//m_vVertexList[3].t = { tEnd / xSize, 1.0f }; */
	//TDevice::m_pd3dContext->UpdateSubresource(
	//	m_pVertexBuffer.Get(), 0, nullptr,
	//	&m_vVertexList.at(0), 0, 0);
}
void TMapObj::SetCellCounter(UINT iRow, UINT iCol)
{
	m_iNumRow = iRow + 1;
	m_iNumCol = iCol + 1;
	m_iNumCellRow = iRow;
	m_iNumCellCol = iCol;
	m_iNumVertex = m_iNumRow * m_iNumCol;
	m_iNumIndex = m_iNumCellRow * m_iNumCellCol * 2 * 3;
}

void	TMapObj::Transform(TVector2 vCamera)
{
	TransformCamera(vCamera);
	TransformNDC();
	TDevice::m_pd3dContext->UpdateSubresource(
		m_pMeshRender->m_pVertexBuffer.Get(), 0, nullptr,
		&m_pMeshRender->m_vVertexList.at(0), 0, 0);
}
void	TMapObj::PreRender()
{
	m_pMeshRender->PreRender();
}
void	TMapObj::Render()
{
	m_pMeshRender->PreRender();
	m_pMeshRender->PostRender();
}
void	TMapObj::PostRender()
{
	if (m_pMeshRender->m_pIndexBuffer == nullptr)
	{
		TDevice::m_pd3dContext->Draw(m_pMeshRender->m_vVertexList.size(), 0);
	}
	else
	{
		srand(time(NULL));
		for (int iCell = 0; iCell < m_iNumCellRow * m_iNumCellCol; iCell++)
		{
			UINT iTex = m_Cells[iCell].iTexID;// rand() % 4;
			TDevice::m_pd3dContext->PSSetShaderResources(
				0, 1, &m_pTexs[iTex]->m_pTexSRV);
			TDevice::m_pd3dContext->DrawIndexed(6, 6 * iCell, 0);
		}
	}
}