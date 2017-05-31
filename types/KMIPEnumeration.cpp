#include "KMIPEnumeration.h"

KMIPEnumeration::KMIPEnumeration(int iTag, uint32_t eValue, uint32_t eFirst, uint32_t eLast) : KMIPNumber(iTag, kmip::TypeEnumeration, eValue) {
    this->eFirst = eFirst;
    this->eLast = eLast;
}

bool KMIPEnumeration::isValid() const {
    return eFirst <= val && val <= eLast;
}

KMIPCredentialType::KMIPCredentialType(uint32_t eValue) : KMIPEnumeration(kmip::TagCredentialType, eValue, KMIPCredentialType::UsernameAndPassword, KMIPCredentialType::Attestation) {}


IMPLEMENT_ENUM_TO_STRING(KMIPCredentialType, VALUE, Unknown, "", CREDENTIAL_TYPE_LIST);
