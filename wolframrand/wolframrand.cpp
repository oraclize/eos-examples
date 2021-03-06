#include "provable/eos_api.hpp"

class wolframrand : public eosio::contract
{
  public:
    using contract::contract;

    wolframrand(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]]
    void getrandomnum()
    {
        provable_query(10, "WolframAlpha", "random number between 1 and 6");
        print(" Provable query was sent, standing by for the answer...");
    }

    [[eosio::action]]
    void callback(
        const eosio::checksum256 queryId,
        const std::vector<uint8_t> result,
        const std::vector<uint8_t> proof
    )
    {
        require_auth(provable_cbAddress());
        const std::string result_str = vector_to_string(result);
        print("Result: ", result_str);
        if (result_str != "6")
          getrandomnum();
    }
};
