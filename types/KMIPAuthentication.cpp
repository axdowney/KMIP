/* Copyright (C) 2017 Alexander Downey */
#include "KMIPAuthentication.h"
#include "KMIPCredential.h"

KMIPAuthentication::KMIPAuthentication() : KMIPStruct(kmip::TagAuthentication) {}

IMPLEMENT_GET_ADD_FIELDS(KMIPAuthentication, KMIPCredential, Credential, kmip::TagCredential);
