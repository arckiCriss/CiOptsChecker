#include <stdio.h>
#include <Windows.h>
#include <winternl.h>

#pragma comment(lib, "ntdll")

int main()
{
	const char* names[] = {
		"CODEINTEGRITY_OPTION_ENABLED",
		"CODEINTEGRITY_OPTION_TESTSIGN",
		"CODEINTEGRITY_OPTION_UMCI_ENABLED",
		"CODEINTEGRITY_OPTION_UMCI_AUDITMODE_ENABLED",
		"CODEINTEGRITY_OPTION_UMCI_EXCLUSIONPATHS_ENABLED",
		"CODEINTEGRITY_OPTION_TEST_BUILD",
		"CODEINTEGRITY_OPTION_PREPRODUCTION_BUILD",
		"CODEINTEGRITY_OPTION_DEBUGMODE_ENABLED",
		"CODEINTEGRITY_OPTION_FLIGHT_BUILD",
		"CODEINTEGRITY_OPTION_FLIGHTING_ENABLED",
		"CODEINTEGRITY_OPTION_HVCI_KMCI_ENABLED",
		"CODEINTEGRITY_OPTION_HVCI_KMCI_AUDITMODE_ENABLED",
		"CODEINTEGRITY_OPTION_HVCI_KMCI_STRICTMODE_ENABLED",
		"CODEINTEGRITY_OPTION_HVCI_IUM_ENABLED"
	};

	const ULONG values[] =
	{
		0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000
	};
	
	SYSTEM_CODEINTEGRITY_INFORMATION information = { sizeof information };
	DWORD cbInfo = 0;
	const auto status = NtQuerySystemInformation(SystemCodeIntegrityInformation,
	                                             &information, information.Length, &cbInfo);
	if (NT_SUCCESS(status))
	{

		for (auto i = 0; i < 14; i++)
			printf("%s=%s\n", names[i], information.CodeIntegrityOptions & values[i] ? "TRUE" : "FALSE");

		printf("\nCodeIntegrityOptions=0x%X\n", information.CodeIntegrityOptions);
	}
	else printf("Failed querying SystemCodeIntegrityInformation\n");
}