create table if not exists auth(
    login varchar primary key,
    passwd varchar,
    port int 
);

create table if not exists messages(
    msg varchar,
    msg_time time
);

create table if not exists friends(
    login varchar,
    friends_login varchar,
    constraint fk_friends_friends_login foreign key (friends_login) references auth(login)
);