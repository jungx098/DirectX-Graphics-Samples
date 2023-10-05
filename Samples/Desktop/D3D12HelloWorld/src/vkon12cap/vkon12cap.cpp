// vkon12cap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "d3d12.h"
#include "d3dx12_check_feature_support.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"

using namespace std;

using Microsoft::WRL::ComPtr;

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        // throw HrException(hr);
        exit(-1);
    }
}

int main()
{
    cout << "Hello World!\n";

    UINT dxgiFactoryFlags = 0;

    ComPtr<IDXGIFactory4> factory;
    ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));

    // ComPtr<IDXGIAdapter1> hardwareAdapter;
    // GetHardwareAdapter(factory.Get(), &hardwareAdapter);

    ComPtr<IDXGIAdapter1> adapter;
    ComPtr<IDXGIFactory6> factory6;
    factory->QueryInterface(IID_PPV_ARGS(&factory6));

    factory6->EnumAdapterByGpuPreference(
        0,
        DXGI_GPU_PREFERENCE_UNSPECIFIED,
        IID_PPV_ARGS(&adapter));

    DXGI_ADAPTER_DESC1 desc;
    adapter->GetDesc1(&desc);

    wcout << desc.Description << endl;

    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
    {
        // Don't select the Basic Render Driver adapter.
        // If you want a software adapter, pass in "/warp" on the command line.
        cout << "Software renderer\n";
        exit(-1);
    }

    ComPtr<ID3D12Device> m_device;
    D3D12CreateDevice(adapter.Get(),
        D3D_FEATURE_LEVEL_11_0,     // Minimum feature level
        // D3D_FEATURE_LEVEL_12_2,
        IID_PPV_ARGS(&m_device));

    CD3DX12FeatureSupport foo;
    foo.Init(m_device.Get());


    cout << "===============================================================\n";
    cout << "Format List Casting";
    cout << " Availability: ";
    if (foo.RelaxedFormatCastingSupported()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- RelaxedFormatCasting: " << foo.RelaxedFormatCastingSupported() << endl;

    cout << "===============================================================\n";
    cout << "Unrestricted Buffer Texture Copy Row Pitch and Offset" << endl;
    cout << " Availability: ";
    if (foo.UnrestrictedBufferTextureCopyPitchSupported()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- UnrestrictedBufferTextureCopyPitch: " << foo.UnrestrictedBufferTextureCopyPitchSupported() << endl;

    cout << "===============================================================\n";
    cout << "Texture Vertex Element Alignment" << endl;
    cout << " Availability: ";
    if (foo.UnrestrictedVertexElementAlignmentSupported()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- UnrestrictedVertexElementAlignment: " << foo.UnrestrictedVertexElementAlignmentSupported() << endl;

    cout << "===============================================================\n";
    cout << "Inverted Viewports" << endl;
    cout << " Availability: ";
    if (foo.InvertedViewportHeightFlipsYSupported() &&
        foo.InvertedViewportDepthFlipsZSupported()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- InvertedViewportHeightFlipsY: " << foo.InvertedViewportHeightFlipsYSupported() << endl;
    cout << "- InvertedViewportDepthFlipsZ: " << foo.InvertedViewportDepthFlipsZSupported() << endl;

    cout << "===============================================================\n";
    cout << "Mixed Renderting Target Resolutions" << endl;
    cout << " Availability: ";
    if (foo.MismatchingOutputDimensionsSupported()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- MismatchingOutputDimensions: " << foo.MismatchingOutputDimensionsSupported() << endl;

    cout << "===============================================================\n";
    cout << "Sample-frequency MSAA with no render targets bound" << endl;
    cout << " Availability: ";
    if (foo.SupportedSampleCountsWithNoOutputs()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- SupportedSampleCountsWithNoOutputs: " << foo.SupportedSampleCountsWithNoOutputs() << endl;

    cout << "===============================================================\n";
    cout << "Changing the spec for point sampling address computations" << endl;
    cout << " Availability: ";
    if (foo.PointSamplingAddressesNeverRoundUp()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- PointSamplingAddressesNeverRoundUp: " << foo.PointSamplingAddressesNeverRoundUp() << endl;

    cout << "===============================================================\n";
    cout << "Line Rasterization Updates" << endl;
    cout << " Availability: ";
    if (foo.RasterizerDesc2Supported() &&
        foo.NarrowQuadrilateralLinesSupported()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- RasterizerDesc2: " << foo.RasterizerDesc2Supported() << endl;
    cout << "- NarrowQuadrilateralLines: " << foo.NarrowQuadrilateralLinesSupported() << endl;

    cout << "===============================================================\n";
    cout << "Anisotropic Sampler with MIP Points" << endl;
    cout << " Availability: ";
    if (foo.AnisoFilterWithPointMipSupported()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- AnisoFilterWithPointMip: " << foo.AnisoFilterWithPointMipSupported() << endl;

    cout << "===============================================================\n";
    cout << "Sampler Descriptor Heap Size Increase" << endl;
    cout << " Availability: ";
    if (foo.MaxSamplerDescriptorHeapSize() &&
        foo.MaxSamplerDescriptorHeapSizeWithStaticSamplers() &&
        foo.MaxViewDescriptorHeapSize()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    cout << "- MaxSamplerDescriptorHeapSize: " << foo.MaxSamplerDescriptorHeapSize() << endl;
    cout << "- MaxSamplerDescriptorHeapSizeWithStaticSamplers: " << foo.MaxSamplerDescriptorHeapSizeWithStaticSamplers() << endl;
    cout << "- MaxViewDescriptorHeapSize: " << foo.MaxViewDescriptorHeapSize() << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
