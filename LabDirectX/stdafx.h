#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN    //Exclude rarely-used stuff from Windows headers.
#endif 

#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h> 
#include <D3Dcompiler.h>
#include <DirectXMath.h> 
#include "d3dx12.h"
#include <string>

//This will only call release if an object exists
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

//Handle to the window 
HWND hwnd = NULL; 

//Name of the window (not the title) 
const LPCTSTR WINDOWNAME = L"BzTutsApp";

//Title of the window
const LPCTSTR WINDOWTITLE = L"Bz Window";

//WIDTH and HEIGHT of the window
int width = 800;
int height = 600;

//Is window full screen?
bool FullScreen = false;
bool FULLSCREEN = false;

//We will exit the program when this becomes false
bool Running = true;

//Create a window
bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	bool fullscreen);

//Main application loop
void mainLoop();

//Callback function for windows messages
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

//Direct3d stuff
const int frameBufferCount = 3; //Number of buffers we want, 2 for double buffering, 3 for tripple buffering

ID3D12Device* device; //Direct3d device

IDXGISwapChain3* swapChain; //Swapchain used to switch between render targets

ID3D12CommandQueue* commandQueue; //Container for command lists

ID3D12DescriptorHeap* rtvDescriptorHeap; //A descriptor heap to hold resources like the render targets

ID3D12Resource* renderTargets[frameBufferCount]; //Number of render targets equal to buffer count

ID3D12CommandAllocator* commandAllocator[frameBufferCount]; //We want enough allocators for each buffer * number of threads (we only have one thread)

ID3D12GraphicsCommandList* commandList; //A command list we can record commands into, then execute them to render the frame

ID3D12Fence* fence[frameBufferCount];    //An object that is locked while our command list is being executed by the gpu. We need as many 
																//as we have allocators (more if we want to know when the gpu is finished with an asset)

HANDLE fenceEvent; //A handle to an event when our fence is unlocked by the gpu

UINT64 fenceValue[frameBufferCount]; //This value is incremented each frame. each fence will have its own value

ID3D12PipelineState* pipelineStateObject;

ID3D12RootSignature* rootSignature;

D3D12_VIEWPORT viewport;

D3D12_RECT scissorRect;

ID3D12Resource* vertexBuffer;

D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

ID3D12Resource* indexBuffer;

D3D12_INDEX_BUFFER_VIEW indexBufferView;

ID3D12Resource* depthStencilBuffer;	//A memory for depth buffer and stencil buffer

ID3D12DescriptorHeap* dsDescriptorHeap;	//A descriptor heap for depth and stencil buffer descriptor

int frameIndex; //Current rtv we are on

int rtvDescriptorSize; //Size of the rtv descriptor on the device (all front and back buffers will be the same size) 

bool InitD3D(); //Initializes direct3d 12

void Update(); //Update the game logic

void UpdatePipeline(); //Update the direct3d pipeline (update command lists)

void Render(); //Execute the command list

void Cleanup(); //Release com ojects and clean up memory

void WaitForPreviousFrame(); //Wait until gpu is finished with command list