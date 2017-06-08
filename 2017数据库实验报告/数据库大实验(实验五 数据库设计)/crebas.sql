/*==============================================================*/
/* DBMS name:      Sybase SQL Anywhere 12                       */
/* Created on:     2017/6/8 21:42:38                            */
/*==============================================================*/


if exists(select 1 from sys.sysforeignkey where role='FK_POLICY_POLICY_EMPLOYEE') then
    alter table Policy
       delete foreign key FK_POLICY_POLICY_EMPLOYEE
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_POLICY_RELATIONS_DEPENDEN') then
    alter table Policy
       delete foreign key FK_POLICY_RELATIONS_DEPENDEN
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_POSITION_BELONG_TO_DEPARTME') then
    alter table Positions
       delete foreign key FK_POSITION_BELONG_TO_DEPARTME
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_WORK_AS_WORK_AS_POSITION') then
    alter table Work_as
       delete foreign key FK_WORK_AS_WORK_AS_POSITION
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_WORK_AS_WORK_AS2_EMPLOYEE') then
    alter table Work_as
       delete foreign key FK_WORK_AS_WORK_AS2_EMPLOYEE
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_WORK_IN_WORK_IN_DEPARTME') then
    alter table Work_in
       delete foreign key FK_WORK_IN_WORK_IN_DEPARTME
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_WORK_IN_WORK_IN2_EMPLOYEE') then
    alter table Work_in
       delete foreign key FK_WORK_IN_WORK_IN2_EMPLOYEE
end if;

drop index if exists Departments.Departments_PK;

drop table if exists Departments;

drop index if exists Dependents.Dependents_PK;

drop table if exists Dependents;

drop index if exists Employees.Employees_PK;

drop table if exists Employees;

drop index if exists Policy.Relationship_9_FK;

drop index if exists Policy.Policy_FK;

drop index if exists Policy.Policy_PK;

drop table if exists Policy;

drop index if exists Positions.Belong_to_FK;

drop index if exists Positions.Positions_PK;

drop table if exists Positions;

drop index if exists Work_as.Work_as_FK;

drop index if exists Work_as.Work_as2_FK;

drop index if exists Work_as.Work_as_PK;

drop table if exists Work_as;

drop index if exists Work_in.Work_in_FK;

drop index if exists Work_in.Work_in2_FK;

drop index if exists Work_in.Work_in_PK;

drop table if exists Work_in;

/*==============================================================*/
/* Table: Departments                                           */
/*==============================================================*/
create table Departments 
(
   did                  integer                        not null,
   dname                varchar(20)                    not null,
   budget               integer                        null,
   constraint PK_DEPARTMENTS primary key (did)
);

/*==============================================================*/
/* Index: Departments_PK                                        */
/*==============================================================*/
create unique index Departments_PK on Departments (
did ASC
);

/*==============================================================*/
/* Table: Dependents                                            */
/*==============================================================*/
create table Dependents 
(
   sname                varchar(20)                    not null,
   s_age                integer                        not null,
   eid                  integer                        not null,
   constraint PK_DEPENDENTS primary key (sname, eid)
);

/*==============================================================*/
/* Index: Dependents_PK                                         */
/*==============================================================*/
create unique index Dependents_PK on Dependents (
sname ASC,
eid ASC
);

/*==============================================================*/
/* Table: Employees                                             */
/*==============================================================*/
create table Employees 
(
   eid                  integer                        not null,
   ename                varchar(20)                    not null,
   d_age                integer                        not null
   	constraint CKC_D_AGE_EMPLOYEE check (d_age between 18 and 65),
   sex                  char(1)                        not null default 'M'
   	constraint CKC_SEX_EMPLOYEE check (sex = upper(sex)),
   constraint PK_EMPLOYEES primary key (eid)
);

/*==============================================================*/
/* Index: Employees_PK                                          */
/*==============================================================*/
create unique index Employees_PK on Employees (
eid ASC
);

/*==============================================================*/
/* Table: Policy                                                */
/*==============================================================*/
create table Policy 
(
   sname                varchar(20)                    not null,
   eid                  integer                        not null,
   cost                 integer                        null,
   constraint PK_POLICY primary key (sname, eid)
);

/*==============================================================*/
/* Index: Policy_PK                                             */
/*==============================================================*/
create unique index Policy_PK on Policy (
sname ASC,
eid ASC
);

/*==============================================================*/
/* Index: Policy_FK                                             */
/*==============================================================*/
create index Policy_FK on Policy (
eid ASC
);

/*==============================================================*/
/* Index: Relationship_9_FK                                     */
/*==============================================================*/
create index Relationship_9_FK on Policy (
sname ASC
);

/*==============================================================*/
/* Table: Positions                                             */
/*==============================================================*/
create table Positions 
(
   pid                  integer                        not null,
   did                  integer                        not null,
   pname                varchar(20)                    not null,
   wage                 integer                        not null,
   constraint PK_POSITIONS primary key (pid)
);

/*==============================================================*/
/* Index: Positions_PK                                          */
/*==============================================================*/
create unique index Positions_PK on Positions (
pid ASC
);

/*==============================================================*/
/* Index: Belong_to_FK                                          */
/*==============================================================*/
create index Belong_to_FK on Positions (
did ASC
);

/*==============================================================*/
/* Table: Work_as                                               */
/*==============================================================*/
create table Work_as 
(
   pid                  integer                        not null,
   eid                  integer                        not null,
   constraint PK_WORK_AS primary key (pid, eid)
);

/*==============================================================*/
/* Index: Work_as_PK                                            */
/*==============================================================*/
create unique index Work_as_PK on Work_as (
pid ASC,
eid ASC
);

/*==============================================================*/
/* Index: Work_as2_FK                                           */
/*==============================================================*/
create index Work_as2_FK on Work_as (
eid ASC
);

/*==============================================================*/
/* Index: Work_as_FK                                            */
/*==============================================================*/
create index Work_as_FK on Work_as (
pid ASC
);

/*==============================================================*/
/* Table: Work_in                                               */
/*==============================================================*/
create table Work_in 
(
   did                  integer                        not null,
   eid                  integer                        not null,
   Location             varchar(20)                    null,
   constraint PK_WORK_IN primary key (did, eid)
);

/*==============================================================*/
/* Index: Work_in_PK                                            */
/*==============================================================*/
create unique index Work_in_PK on Work_in (
did ASC,
eid ASC
);

/*==============================================================*/
/* Index: Work_in2_FK                                           */
/*==============================================================*/
create index Work_in2_FK on Work_in (
eid ASC
);

/*==============================================================*/
/* Index: Work_in_FK                                            */
/*==============================================================*/
create index Work_in_FK on Work_in (
did ASC
);

alter table Policy
   add constraint FK_POLICY_POLICY_EMPLOYEE foreign key (eid)
      references Employees (eid)
      on update restrict
      on delete restrict;

alter table Policy
   add constraint FK_POLICY_RELATIONS_DEPENDEN foreign key (sname, )
      references Dependents (sname, eid)
      on update restrict
      on delete restrict;

alter table Positions
   add constraint FK_POSITION_BELONG_TO_DEPARTME foreign key (did)
      references Departments (did)
      on update restrict
      on delete restrict;

alter table Work_as
   add constraint FK_WORK_AS_WORK_AS_POSITION foreign key (pid)
      references Positions (pid)
      on update restrict
      on delete restrict;

alter table Work_as
   add constraint FK_WORK_AS_WORK_AS2_EMPLOYEE foreign key (eid)
      references Employees (eid)
      on update restrict
      on delete restrict;

alter table Work_in
   add constraint FK_WORK_IN_WORK_IN_DEPARTME foreign key (did)
      references Departments (did)
      on update restrict
      on delete restrict;

alter table Work_in
   add constraint FK_WORK_IN_WORK_IN2_EMPLOYEE foreign key (eid)
      references Employees (eid)
      on update restrict
      on delete restrict;

