#include "Certificate.h"

#include <stdio.h>
#include <stdlib.h>

int initCertificate(Certificate* pCer, int certificateId)
{
	pCer->animalCertificateId = certificateId;
	pCer->countryOfOrigin = getStrExactName("Enter country of origin");
	if (!pCer->countryOfOrigin)
		return 0;
	pCer->animalDescription = getStrExactName("Enter a short description of the animal breed (255 max string lenght)");
	if (!pCer->animalDescription)
		return 0;
	return 1;
}

int	saveCertificateToTextFile(const Certificate* pCer, FILE* fp)
{
	if (!writeIntToFile(pCer->animalCertificateId, fp, "Error writing id to text file\n"))
		return 0;
	if (!writeStringToTextFile(pCer->countryOfOrigin, fp, "Error writing country to text file\n"))
		return 0;
	if (!writeStringToTextFile(pCer->animalDescription, fp, "Error writing description to text file\n"))
		return 0;
	return 1;
}

int	loadCertificateFromTextFile(Certificate* pCer, FILE* fp)
{
	if (!readIntFromTextFile(&pCer->animalCertificateId, fp, "Error reading id from text file\n"))
		return 0;
	pCer->countryOfOrigin = readDynStringFromTextFile(fp);
	pCer->animalDescription = readDynStringFromTextFile(fp);
	return 1;
}

int	saveCertificateToBinaryFile(const Certificate* pCer, FILE* fp)
{
	if (!writeIntToFile(pCer->animalCertificateId, fp, "Error writing id to binary file\n"))
		return 0;
	if (!writeStringToFile(pCer->countryOfOrigin, fp, "Error writing country to binary file\n"))
		return 0;
	if (!writeStringToFile(pCer->animalDescription, fp, "Error writing description to binary file\n"))
		return 0;
	return 1;
}

int	loadCertificateFromBinaryFile(Certificate* pCer, FILE* fp)
{
	if (!readIntFromFile(&pCer->animalCertificateId, fp, "Error reading id from binary file\n"))
		return 0;
	pCer->countryOfOrigin = readStringFromFile(fp, "Error reading country from binary file\n");
	pCer->animalDescription = readStringFromFile(fp, "Error reading description from binary file\n");
	return 1;
}

void printCertificate(const Certificate* pCer)
{
	printf("Certificate ID of the animal: %d\n", pCer->animalCertificateId);
	printf("Country of origin: %s\n", pCer->countryOfOrigin);
	printf("A short description: %s\n", pCer->animalDescription);
}

void freeCertificate(Certificate* pCer)
{
	free(pCer->countryOfOrigin);
	free(pCer->animalDescription);
}