#include "TMapObj.h"
#include "TDevice.h"
#include <time.h>
void TMapObj::Frame()
{
	//srand(time(NULL));
	//UINT iVertex = rand() % m_vVertexList.size();
	/*for (int i = 0; i < m_vVertexList.size(); i++)
	{
		m_vVertexList[i].v.x += g_fSPF * cosf(g_fGT);
	}*/

	//static float tStart = 0.0f;
	//static float tEnd = 1000.0f;
	//tStart += g_fSPF * 0.0f;
	//tEnd   += g_fSPF * 0.0f;
	//UINT xSize = m_pTexture->m_TexDesc.Width;
	//UINT ySize = m_pTexture->m_TexDesc.Height;
	//m_vVertexList[0].t = { 0.0f,tStart / ySize };
	//m_vVertexList[1].t = { 1.0f,tStart / ySize };
	//m_vVertexList[2].t = { 0.0f,tEnd / ySize };
	//m_vVertexList[3].t = { 1.0f,tEnd / ySize };
	///*m_vVertexList[0].t = { tStart / xSize, 0.0f };
	//m_vVertexList[1].t = { tEnd / xSize, 0.0f };
	//m_vVertexList[2].t = { tStart / xSize, 1.0f };
	//m_vVertexList[3].t = { tEnd / xSize, 1.0f }; */
	TDevice::m_pd3dContext->UpdateSubresource(
		m_pVertexBuffer.Get(), 0, nullptr,
		&m_vVertexList.at(0), 0, 0);
}
void TMapObj::UpdateVertexData()
{
	if (m_pTexture == nullptr) return;
	
	/*UINT xSize = m_pTexture->m_TexDesc.Width;
	UINT ySize = m_pTexture->m_TexDesc.Height;
	
	m_vVertexList[0].t = { 0.0f,0.0f };
	m_vVertexList[1].t = { 1.0f,0.0f };
	m_vVertexList[2].t = { 0.0f,140.0f / ySize };
	m_vVertexList[3].t = { 1.0f,140.0f / ySize };
	TDevice::m_pd3dContext->UpdateSubresource(
		m_pVertexBuffer.Get(), 0, nullptr,
		&m_vVertexList.at(0), 0, 0);*/
}
void TMapObj::SetVertexData()
{
	m_iNumRow = 9;
	m_iNumCol = 9;
	m_iNumCellRow = m_iNumRow - 1;
	m_iNumCellCol = m_iNumCol - 1;
	m_iNumVertex = m_iNumRow * m_iNumCol;
	m_iNumIndex = m_iNumCellRow * m_iNumCellCol * 2 * 3;
	//TObject::SetVertexData();	
	m_vVertexList.resize(m_iNumRow * m_iNumCol);
	// 0  1  2  
	// 3  4  5 
	// 6  7  8
	// iNumCell  = (3-1) * (3-1)

	float fOffsetU = 1.0f / m_iNumCellCol;
	float fOffsetV = 1.0f / m_iNumCellRow;
	for (UINT iRow = 0; iRow < m_iNumRow; iRow++)
	{
		for (UINT iCol = 0; iCol < m_iNumCol; iCol++)
		{
			float x = iCol * g_WindowSize.x / (m_iNumCol-1);
			float y = iRow * g_WindowSize.y / (m_iNumRow-1);
			m_vVertexList[iRow * m_iNumRow + iCol].v = ScreenToNDC(x, y, g_WindowSize);
			m_vVertexList[iRow * m_iNumRow + iCol].c = { iCol / 2.0f, iRow / 2.0f, 1.0f,1.0f };
			m_vVertexList[iRow * m_iNumRow + iCol].t.x = iCol;
			m_vVertexList[iRow * m_iNumRow + iCol].t.y = iRow;
		}
	}
}
void TMapObj::SetIndexData()
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

			iIndex += 6;
		}
	}

	m_pTexs[0] = I_Tex.Load(L"../../data/texture/bitmap1.bmp");
	m_pTexs[1] = I_Tex.Load(L"../../data/texture/bitmap2.bmp");
	m_pTexs[2] = I_Tex.Load(L"../../data/texture/hero.png");
	m_pTexs[3] = I_Tex.Load(L"../../data/texture/kgcalogo.bmp");
}

void	TMapObj::PostRender()
{
	if (m_pIndexBuffer == nullptr)
		TDevice::m_pd3dContext->Draw(m_vVertexList.size(), 0);
	else
	{
		srand(time(NULL));
		for (int iCell = 0; iCell < m_iNumCellRow* m_iNumCellCol; iCell++)
		{
			UINT iTex = rand() % 4;
			TDevice::m_pd3dContext->PSSetShaderResources(
				0, 1, &m_pTexs[iTex]->m_pTexSRV);
			TDevice::m_pd3dContext->DrawIndexed(6,6*iCell, 0);
		}
	}
}