// TryCreatePackageDependencyRepro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <wil/cppwinrt.h>
#include <wil/com.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef GetCurrentTime

#include <winuser.h>

#include <wil/win32_helpers.h>
#include <wil/resource.h>
#include <wil/stl.h>

#include <appmodel.h>

int main()
{
    auto func = [](std::wstring_view pfn) {

        //auto kernelbase = LoadLibraryW(L"kernelbase");
        //auto tryCreatePackageDependency = reinterpret_cast<decltype(&TryCreatePackageDependency)>(GetProcAddress(kernelbase, "TryCreatePackageDependency"));
        wil::unique_process_heap_string packageId;
        HRESULT hr = TryCreatePackageDependency(nullptr, pfn.data(), {},
            PackageDependencyProcessorArchitectures::PackageDependencyProcessorArchitectures_X64,
            PackageDependencyLifetimeKind::PackageDependencyLifetimeKind_Process,
            nullptr,
            CreatePackageDependencyOptions::CreatePackageDependencyOptions_None,
            &packageId);
        if (SUCCEEDED(hr))
        {
            //auto addPackageDependency = reinterpret_cast<decltype(&AddPackageDependency)>(GetProcAddress(kernelbase, "AddPackageDependency"));

            wil::unique_process_heap_string packageFullName;
            PACKAGEDEPENDENCY_CONTEXT context;
            hr = AddPackageDependency(packageId.get(), 0, AddPackageDependencyOptions::AddPackageDependencyOptions_None, &context, &packageFullName);
        }
    };

    func(L"Microsoft.UI.Xaml.CBS_8wekyb3d8bbwe");
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
