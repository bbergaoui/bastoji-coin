// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>
#include "arith_uint256.h"

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The Times 31/Aug/2018 Sqoin team created bastoji coin";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
	genesis = CreateGenesisBlock(1534754593,876527, 0x1e0ffff0, 1, 50 * COIN);

   	  	    /*	  		bool fNegative;
    	    	    	  		bool fOverflow;
    	    	    	  		uint32_t i=0;



    	    	    			while (true) {
    	    	    					genesis = CreateGenesisBlock(1534754593,i, 0x1e0ffff0, 1, 50 * COIN);

    	    	    				arith_uint256 bnTarget;

    	    	    				bnTarget.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        	    			if (UintToArith256(genesis.GetHash()) > bnTarget) {
    	  	    					//std::cout << " nonce not correct  \n";
    	    	    			//		std::cout << i << " ";
    	    	    					i++;
        	    				}
    	    	    				else {
    	    	    					std::cout << " nonce found  " << i << "\n";
    	    	    					std::cout << " genesis found  " <<  genesis.GetHash().ToString() << "\n";
    	    	    					//break;
    	    	    							exit(-1);
    	    	    				}
    	    	    				} */





    	 	 	strNetworkID = "main";
    	        consensus.nSubsidyHalvingInterval = 210000;
    	        consensus.BIP16Exception = uint256();
    	        consensus.BIP34Height = 0;
    	        consensus.BIP34Hash = uint256();
    	        consensus.BIP65Height = 0;
    	        consensus.BIP66Height = 0;
    	        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    	        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
    	        consensus.nPowTargetSpacing = 10 * 60;
    	        consensus.fPowAllowMinDifficultyBlocks = false;
    	        consensus.fPowNoRetargeting = true;
    	        consensus.nRuleChangeActivationThreshold = 1916; // 75% for testchains
    	        consensus.nMinerConfirmationWindow = 2016;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1534701725;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1534701725;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
    	        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

    	        // The best chain should have at least this much work.
    	        consensus.nMinimumChainWork = uint256S("0x00");

    	        // By default assume that the signatures in ancestors of this block are valid.
    	        consensus.defaultAssumeValid = uint256S("0x00");

    	        pchMessageStart[0] = 0xfa;
    	        pchMessageStart[1] = 0xbf;
    	        pchMessageStart[2] = 0xb5;
    	        pchMessageStart[3] = 0xda;
    	        nDefaultPort = 7232;
    	        nPruneAfterHeight = 1000;

    	        consensus.hashGenesisBlock = genesis.GetHash();
    	 //       std::cout<< ( consensus.hashGenesisBlock.ToString());
//    	        std::cout << "------------------" << consensus.hashGenesisBlock.ToString() << "--------";
//    	        std::cout << "------------------" << genesis.GetHash().ToString() << "--------";
    	  assert(consensus.hashGenesisBlock  == uint256S("00000f78e433fbfe0780d9ff2daf52de590fe36935c23fac99ad107078223acd"));
    	        //assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
    	        //assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));

    	        vFixedSeeds.clear();
    	        vSeeds.clear();

    	        vSeeds.emplace_back("dns1.bastoji.com");
    	        vSeeds.emplace_back("dns2.bastoji.com");
    	        vSeeds.emplace_back("dns3.bastoji.com");

    	        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));



    	        fDefaultConsistencyChecks = false;
    	        fRequireStandard = true;
    	        fMineBlocksOnDemand = false;

    	        checkpointData = {
    	            {
    	                {0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")},
    	            }
    	        };

    	        chainTxData = ChainTxData{
    	            0,
    	            0,
    	            0
    	        };

    	        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
    	        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
    	        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
    	        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
    	        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

    	        bech32_hrp = "bcrt";

    	        /* enable fallback fee on regtest */
    	        m_fallback_fee_enabled = true;
    	    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
    	genesis = CreateGenesisBlock(1534754595,935199, 0x1e0ffff0, 1, 20 * COIN);

/*
    	   	    	    	  		bool fNegative;
    	    	    	    	  		bool fOverflow;
    	    	    	    	  		uint32_t i=0;



    	    	    	    			while (true) {
    	    	    	    					genesis = CreateGenesisBlock(1534754595,i++, 0x1e0ffff0, 1, 20 * COIN);

    	    	    	    				arith_uint256 bnTarget;

    	    	    	    				bnTarget.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
    	        	    			if (UintToArith256(genesis.GetHash()) > bnTarget) {
    	    	  	    					std::cout << " nonce not correct  \n";
    	    	    	    					std::cout << i << " ";
    	        	    				}
    	    	    	    				else {
    	    	    	    					std::cout << " nonce found  " << i << "\n";
    	    	    	    					std::cout << " genesis found  " <<  genesis.GetHash().ToString() << "\n";
    	    	    	    					//break;
    	    	    	    							exit(-1);
    	    	    	    				}
    	    	    	    				}
    	    	    	    				*/





    	    	 strNetworkID = "test";
    	    	        consensus.nSubsidyHalvingInterval = 150;
    	    	        consensus.BIP16Exception = uint256();
    	    	        consensus.BIP34Height = 0;
    	    	        consensus.BIP34Hash = uint256();
    	    	        consensus.BIP65Height = 0;
    	    	        consensus.BIP66Height = 0;
    	    	        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    	    	        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
    	    	        consensus.nPowTargetSpacing = 10 * 60;
    	    	        consensus.fPowAllowMinDifficultyBlocks = true;
    	    	        consensus.fPowNoRetargeting = true;
    	    	        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
    	    	        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1534701725;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1534701725;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
    	    	        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

    	    	        // The best chain should have at least this much work.
    	    	        consensus.nMinimumChainWork = uint256S("0x00");

    	    	        // By default assume that the signatures in ancestors of this block are valid.
    	    	        consensus.defaultAssumeValid = uint256S("0x00");

    	    	        pchMessageStart[0] = 0xfa;
    	    	        pchMessageStart[1] = 0xbf;
    	    	        pchMessageStart[2] = 0xb5;
    	    	        pchMessageStart[3] = 0xda;
    	    	        nDefaultPort = 7233;
    	    	        nPruneAfterHeight = 1000;

    	    	        consensus.hashGenesisBlock = genesis.GetHash();
    	    	       // std::cout << "------------------" << consensus.hashGenesisBlock.ToString() << "--------";
    	    	       // std::cout << "------------------" << genesis.GetHash().ToString() << "--------";
    	  //  	  assert(consensus.hashGenesisBlock  == uint256S("00000c7cdc5432d59fcddd69f27e4c915dcd1ef0af49f4c7e859aec16082389b"));
    	    	        //assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
    	    	        //assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));

    	    	        vFixedSeeds.clear();
    	    	        vSeeds.clear();

    	    	        vSeeds.emplace_back("demystifytokens.com");
    	    	        vSeeds.emplace_back("demystifytokens2.com");
    	    	        vSeeds.emplace_back("demystifytokens3.com");
    	    	        vSeeds.emplace_back("demystifytokens10.com");

    	    	        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_test));



    	    	        fDefaultConsistencyChecks = false;
    	    	        fRequireStandard = true;
    	    	        fMineBlocksOnDemand = false;

    	    	        checkpointData = {
    	    	            {
    	    	                {0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")},
    	    	            }
    	    	        };

    	    	        chainTxData = ChainTxData{
    	    	            0,
    	    	            0,
    	    	            0
    	    	        };

    	    	        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
    	    	        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
    	    	        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
    	    	        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
    	    	        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

    	    	        bech32_hrp = "bcrt";

    	    	        /* enable fallback fee on regtest */
    	    	        m_fallback_fee_enabled = true;
    	    	    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
		genesis = CreateGenesisBlock(1296688602,760129, 0x207fffff, 1, 30 * COIN);

/*
    	bool fNegative;
    	    	    	    	  		bool fOverflow;
    	    	    	    	  		uint32_t i=0;



    	    	    	    			while (true) {
    	    	    	    					genesis = CreateGenesisBlock(1296688602,++i, 0x207fffff, 1, 30 * COIN);
    	    	    	    				arith_uint256 bnTarget;

    	    	    	    				bnTarget.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
    	        	    			if (UintToArith256(genesis.GetHash()) > bnTarget) {
    	    	  	    					std::cout << " nonce not correct  \n";
    	    	    	    					std::cout << i << " ";
    	        	    				}
    	    	    	    				else {
    	    	    	    					std::cout << " nonce found  " << i << "\n";
    	    	    	    					std::cout << " genesis found  " <<  genesis.GetHash().ToString() << "\n";

    	    	    	    							exit(-1);
    	    	    	    				}
    	    	    	    				}
*/

        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = -1;
        consensus.BIP66Height = -1;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1534701725;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1534701725;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 7232 ;
        nPruneAfterHeight = 1000;

        //genesis = CreateGenesisBlock(1296688602, 2, 0x207fffff, 1, 50 * COIN);
           	        consensus.hashGenesisBlock = genesis.GetHash();
           	         assert( consensus.hashGenesisBlock  == uint256S("00000a700a37fa931860aa082acd4da286c4a6f0bae9f3cc286f1c5bd6b3fafb"));
        //assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
        //assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.


        vSeeds.emplace_back("demystifytokens1.com");
        vSeeds.emplace_back("demystifytokens2.com");
        vSeeds.emplace_back("demystifytokens3.com");
        vSeeds.emplace_back("demystifytokens10.com");

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "bcrt";

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
