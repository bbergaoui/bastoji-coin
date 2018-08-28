// Copyright (c) 2011-2014 The Bastoji Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BASTOJI_QT_BASTOJIADDRESSVALIDATOR_H
#define BASTOJI_QT_BASTOJIADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BastojiAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BastojiAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Bastoji address widget validator, checks for a valid bastoji address.
 */
class BastojiAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BastojiAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BASTOJI_QT_BASTOJIADDRESSVALIDATOR_H
