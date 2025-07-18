<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: src/proto/grpc/testing/messages.proto

namespace Grpc\Testing\HookRequest;

use UnexpectedValueException;

/**
 * Protobuf type <code>grpc.testing.HookRequest.HookRequestCommand</code>
 */
class HookRequestCommand
{
    /**
     * Default value
     *
     * Generated from protobuf enum <code>UNSPECIFIED = 0;</code>
     */
    const UNSPECIFIED = 0;
    /**
     * Start the HTTP endpoint
     *
     * Generated from protobuf enum <code>START = 1;</code>
     */
    const START = 1;
    /**
     * Stop
     *
     * Generated from protobuf enum <code>STOP = 2;</code>
     */
    const STOP = 2;
    /**
     * Return from HTTP GET/POST
     *
     * Generated from protobuf enum <code>RETURN = 3;</code>
     */
    const PBRETURN = 3;

    private static $valueToName = [
        self::UNSPECIFIED => 'UNSPECIFIED',
        self::START => 'START',
        self::STOP => 'STOP',
        self::PBRETURN => 'RETURN',
    ];

    public static function name($value)
    {
        if (!isset(self::$valueToName[$value])) {
            throw new UnexpectedValueException(sprintf(
                    'Enum %s has no name defined for value %s', __CLASS__, $value));
        }
        return self::$valueToName[$value];
    }


    public static function value($name)
    {
        $const = __CLASS__ . '::' . strtoupper($name);
        if (!defined($const)) {
            $pbconst =  __CLASS__. '::PB' . strtoupper($name);
            if (!defined($pbconst)) {
                throw new UnexpectedValueException(sprintf(
                        'Enum %s has no value defined for name %s', __CLASS__, $name));
            }
            return constant($pbconst);
        }
        return constant($const);
    }
}

