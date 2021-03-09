// Buy 
// buy price is x
// we are interested in sell price y , y <= x
// keep (sell_orders)
// sell_orders[i].price < sell_orders[i + 1].price
// sell_orders[i].price == sell_orders[i + 1].price => 
// sell_orders[i].time < sell_orders[i + 1].time
// (price , time) , price is ascending order , time is in ascending order


// Sell 
// sell price is x
// we are interested in buy price y , y >= x
// keep (buy_orders)
// buy_orders[i].price > buy_orders[i + 1].price
// buy_orders[i].price == buy_orders[i + 1].price =>
// sell_orders[i].time < sell_orders[i + 1].time
// (price , time) , price in descending order , time in ascending order
multiset for sell list
multiset for buy list
unordered_map<pair<string , long> , Order>> mp_buy , mp_sell;
set<int> sell_prices , buy_prices;
unordered_map<int , long> sellvolumn , buyvolumn;



given (username , order_id)
if(mp_buy[username].find(order_id) != mp_buy[username].end()){
    // process buy
    1. buyOrder b = mp[username][order_id]
    2. blist.erase(blist.find(b));
    O(logN) for find(b)
    O(1) for erase
}
else if(mp_sell[username].find(order_id) != mp_sell[username].end()){
    // process sell
    ...
}




set<int> getpricelevel(side){
    return side == buy ? buy_prices : sell_prices; // O(1)
}



long getvolumnatlevel(side , price){
    return side == buy ? buyvolumn[price] : sellvolumn[price];
}
// total volumn

map[(string , order_id)] = {information for this order}
and we can use mutiset's find to find the iterator for this order
and then erase

multiset<SellOrder> slist;
multiset<BuyOrder> blist;

vector<Trade> submitSell(SellOrder order){
    // order will have attributes : (price , time , volumn , id ...)
    // find all trades that can happen with this order
    while(blist.empty() && order.volumn > 0){
        1. get the first buyOrder of blist
        2. check the price of this buy order
            if(price < order.price)break
            3. get the amount of volumn that we can trade for 
                the amount = min(order.volumn , buy_volumn)
                generate a trade (price = buy_price , volumn = amount ...)
                order.volumn -= amount
                buy_volumn -= amount
                buyvolumn[buy_price] -= amount
                if(buy_volumn <= 0){
                    er
                    ase(this buy order from blist)
                }
    }
    if(order.volumn > 0){
        slist.insert(order);    
        sell_price.insert(order.price);   
        sellvolumn[order.price] += order.volumn
    }
}















