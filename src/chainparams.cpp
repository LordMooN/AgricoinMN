// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        //using HAVW in hex
        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x57;
        vAlertPubKey = ParseHex("04f4agc230591895a2a274a733989e10bd15f9cf7bfc26fcfc2d72d584378bd208c59f7809220154bd808b53ccbd422e864f359105f277a30026752fd404a0fc76");
        nDefaultPort = 21212;
        nRPCPort = 21213;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=0f1c683e664955996db18ef7d827d0ed69e168cf6055df8ea4ea7c80936d907c, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=3b6629fee8b425f74965a84b6c4e0c88732b041df879b1d5bf7f7db8981c4efc, nTime=1504607927, nBits=1e0ffff0, nNonce=450467, vtx=1, vchBlockSig=);
        //Coinbase(hash=12630d16a9, nTime=1504607927, ver=1, vin.size=1, vout.size=1, nLockTime=0);
        //CTxIn(COutPoint(0000000000, 4294967295), coinbase 4fd97621e34c6c637a837d1b2eefbb1922795d680130b270b7a30a547042d3c6);
        //CTxOut(empty);
        //vMerkleTree: 12630d16a9;
        const char* pszTimestamp = "AGCMN Peer to Peer Lending";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1504607927, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1526595323;
        genesis.nBits    = 504365040; 
        genesis.nNonce   = 111139;





        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000ab966c20fe8434563a81b905268c0437ca5e31e3fe79d5a2524fb4fa4bd8"));
        assert(genesis.hashMerkleRoot == uint256("0xd8a7d9b618268b19edf6ee1c5dc3f0c2aebec6252310770bfc0ae5ece9e8fa93"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,113);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,115);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,117);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x03)(0x88)(0xC3)(0x2E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x03)(0x88)(0xD3)(0xE2).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0",  "seed0.agricoin.asia"));
        vSeeds.push_back(CDNSSeedData("1",  "seed1.agricoin.asia"));
        vSeeds.push_back(CDNSSeedData("2",  "seed2.agricoin.asia"));
        vSeeds.push_back(CDNSSeedData("3",  "seed3.agricoin.asia"));
        vSeeds.push_back(CDNSSeedData("4",  "seed4.agricoin.asia"));
        vSeeds.push_back(CDNSSeedData("5",  "seed5.agricoin.asia"));
        vSeeds.push_back(CDNSSeedData("6",  "seed6.agricoin.asia"));
         convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "ZUDZ9cKvK2vrWUGLhJXhknpNSAGF6TJCYt";
        nLastPOWBlock = 1000;
        nPOSStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x54;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04f4agc230591895a2a274a733989e10bd15f9cf7bfc26fcfc2d72d584378bd208c59f7809220154bd808b53ccbd422e864f359105f277a30026752fd404a0fc76");
        nDefaultPort = 7878;
        nRPCPort = 7979;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 504365040; 
       genesis.nNonce   = 111139;
        
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000ab966c20fe8434563a81b905268c0437ca5e31e3fe79d5a2524fb4fa4bd8"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,156);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,135);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,123);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,83);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x13)(0x06)(0x16)(0x27).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x13)(0x05)(0x17)(0x34).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 5000;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
